// image.h

#ifndef _IMAGE_H_
#define _IMAGE_H_

class CImage : public CDIBSurface
{
    DECLARE_DYNCREATE(CImage);
public:
    CImage();
    virtual ~CImage();
};

#endif // _IMAGE_H_

