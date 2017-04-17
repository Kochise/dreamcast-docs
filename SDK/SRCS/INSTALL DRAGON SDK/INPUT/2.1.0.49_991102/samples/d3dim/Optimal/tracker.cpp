/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1998 Microsoft Corporation

Module Name:

    Tracker.cxx

Abstract:

    CTracker implementation

-------------------------------------------------------------------*/

// ++++ Include Files +++++++++++++++++++++++++++++++++++++++++++++++
#include "Optimal.hpp"

void matprod(D3DMATRIX *md, D3DMATRIX *ms1, D3DMATRIX *ms2);

CTracker *g_ptrackerStrip = NULL;

void CTracker::Randomize(float rX, float rY, float rZ)
{
	// Randomize translation and rotation info
    m_matRotAndTrans = m_matOrientation =  g_matIdent;
    m_matOrientation._41 = rX;
    m_matOrientation._42 = rY;
    m_matOrientation._43 = rZ;

    m_rXRot = (-1.0f + (float)(rand()%100)/50.0f)/4.0f;
    m_rYRot = (-1.0f + (float)(rand()%100)/50.0f)/4.0f;
    m_rZRot = (-1.0f + (float)(rand()%100)/50.0f)/4.0f;

    m_rXTrans = (-1.0f + (float)(rand()%100)/50.0f)/4.0f;
    m_rYTrans = (-1.0f + (float)(rand()%100)/50.0f)/4.0f;
    SetMatrix();
}

void CTracker::SetMatrix()
{
    D3DMATRIX matRotate;

    D3DVECTOR vAxisX(1.0f, 0.0f, 0.0f);
    D3DVECTOR vAxisY(0.0f, 1.0f, 0.0f);
    D3DVECTOR vAxisZ(0.0f, 0.0f, 1.0f);

    SetMatrixAxisRotation(&matRotate, &vAxisX, m_rXRot);
    m_matRotAndTrans = matRotate;
    SetMatrixAxisRotation(&matRotate, &vAxisY, m_rYRot);
    matprod(&m_matRotAndTrans, &m_matRotAndTrans, &matRotate);
    SetMatrixAxisRotation(&matRotate, &vAxisZ, m_rZRot);
    matprod(&m_matRotAndTrans, &m_matRotAndTrans, &matRotate);
}

void CTracker::Move()
{
    matprod(&m_matOrientation, &m_matRotAndTrans, &m_matOrientation);
    g_p3ddevice->SetTransform(D3DTRANSFORMSTATE_WORLD, &m_matOrientation);
}

void
matprod(D3DMATRIX *pmatDest, D3DMATRIX *pmatSource1, D3DMATRIX *pmatSource2)
{
    // TODO: This will eventually use Quadword-moves for better speed
    __asm (
            "fmov.s fr8,  @-r15\n"
            "fmov.s fr9,  @-r15\n"
            "fmov.s fr10, @-r15\n"
            "fmov.s fr11, @-r15\n"
            "fmov.s fr12, @-r15\n"
            "fmov.s fr13, @-r15\n"
            "fmov.s fr14, @-r15\n"
            "fmov.s fr15, @-r15\n"

           "fmov.s @r6+, fr0\n"
           "fmov.s @r6+, fr1\n"
           "fmov.s @r6+, fr2\n"
           "fmov.s @r6+, fr3\n"
           "fmov.s @r6+, fr4\n"
           "fmov.s @r6+, fr5\n"
           "fmov.s @r6+, fr6\n"
           "fmov.s @r6+, fr7\n"
           "fmov.s @r6+, fr8\n"
           "fmov.s @r6+, fr9\n"
           "fmov.s @r6+, fr10\n"
           "fmov.s @r6+, fr11\n"
           "fmov.s @r6+, fr12\n"
           "fmov.s @r6+, fr13\n"
           "fmov.s @r6+, fr14\n"
           "fmov.s @r6+, fr15\n"


            "; Swap the floating point bank register bit so that we're writing into the other set of FP registers.\n"
            "frchg\n"

            "; Now move the second matrix into the floating point registers\n"
            "fmov.s @r5+, fr0\n"
            "fmov.s @r5+, fr1\n"
            "fmov.s @r5+, fr2\n"
            "fmov.s @r5+, fr3\n"
            "fmov.s @r5+, fr4\n"
            "fmov.s @r5+, fr5\n"
            "fmov.s @r5+, fr6\n"
            "fmov.s @r5+, fr7\n"
            "fmov.s @r5+, fr8\n"
            "fmov.s @r5+, fr9\n"
            "fmov.s @r5+, fr10\n"
            "fmov.s @r5+, fr11\n"
            "fmov.s @r5+, fr12\n"
            "fmov.s @r5+, fr13\n"
            "fmov.s @r5+, fr14\n"
            "fmov.s @r5,  fr15\n"

	        "; Do the actual vector multiplications\n"
	        "ftrv xmtrx, fv0\n"
	        "ftrv xmtrx, fv4\n"
	        "ftrv xmtrx, fv8\n"
	        "ftrv xmtrx, fv12\n"

	        "; Finally copy the results out to the destination matrix.\n"

	        "; Pre-increment the destination address so we can pre-decrement r4 inline\n"
	        "add #60, r4\n"

            "fmov.s fr15, @r4\n"
            "fmov.s fr14, @-r4\n"
            "fmov.s fr13, @-r4\n"
            "fmov.s fr12, @-r4\n"
            "fmov.s fr11, @-r4\n"
            "fmov.s fr10, @-r4\n"
            "fmov.s fr9, @-r4\n"
            "fmov.s fr8, @-r4\n"
            "fmov.s fr7, @-r4\n"
            "fmov.s fr6, @-r4\n"
            "fmov.s fr5, @-r4\n"
            "fmov.s fr4, @-r4\n"
            "fmov.s fr3, @-r4\n"
            "fmov.s fr2, @-r4\n"
            "fmov.s fr1, @-r4\n"
            "fmov.s fr0, @-r4\n"

            "; Swap the floating point bank register bit back to it's original value.\n"
            "frchg   ; todo - move to after the 'rts' to avoid pipeline stall\n"

            "fmov.s @r15+, fr15\n"
            "fmov.s @r15+, fr14\n"
            "fmov.s @r15+, fr13\n"
            "fmov.s @r15+, fr12\n"
            "fmov.s @r15+, fr11\n"
            "fmov.s @r15+, fr10\n"
            "fmov.s @r15+, fr9\n"
            "fmov.s @r15+, fr8\n"


           ,pmatDest, pmatSource1, pmatSource2);

}
