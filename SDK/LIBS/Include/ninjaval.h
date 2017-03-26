/*
	Ninja Library
	
	COPYRIGHT (C) SEGA ENTERPRISES,LTD.
*/

#ifndef	_NINJA_VAL_H_
#define	_NINJA_VAL_H_

extern  NJS_SCREEN	_nj_screen_;
extern  NJS_VIEW	*_nj_view_;
extern  NJS_MATRIX  _nj_view_matrix_;
extern  NJS_MATRIX	*_nj_current_matrix_ptr_;
extern  NJS_MATRIX	*_nj_base_matrix_ptr_;
extern  NJS_POINT2  _nj_2d_clip_[2];
extern  Float       _nj_near_clip_;
extern  Float       _nj_far_clip_;
extern  Float       _nj_scr_aspect_x_;
extern  Float       _nj_scr_aspect_y_;
extern 	Int			_nj_display_mode_;
extern	Int			_nj_frame_mode_;
extern	Int			_nj_waitvsync_count;

extern	Uint32		_nj_control_3d_flag_;

extern Uint32 _nj_vertex_buffer_op_;
extern Uint32 _nj_vertex_buffer_om_;
extern Uint32 _nj_vertex_buffer_tp_;
extern Uint32 _nj_vertex_buffer_tm_;
extern Uint32 _nj_vertex_buffer_pt_;


extern Uint32 _nj_start_vertex_op;
extern Uint32 _nj_start_vertex_om;
extern Uint32 _nj_start_vertex_tp;
extern Uint32 _nj_start_vertex_tm;
extern Uint32 _nj_start_vertex_pt;

extern Int _nj_frame_size_w;
extern Int _nj_frame_size_h;

/******************************/
/* Global Variable for Model  */
extern	NJS_VERTEX_BUF	*_nj_vertex_buf_;
extern	Int	_nj_vertex_num_;

extern	Int	_nj_calc_vertex_;
extern	Int	_nj_calc_polygon_;
extern	Int	_nj_draw_polygon_;
extern	Uint32	_nj_constant_attr_and_;
extern	Uint32	_nj_constant_attr_or_;
extern	NJS_ARGB	_nj_constant_material_;
extern	Uint32	_nj_cnk_blend_mode_;

extern	Uint32	_nj_vsync_count_;
extern	Float	_nj_depth_near_;
extern	Float	_nj_depth_far_;
extern	Float	_nj_depth_range_;
extern	Float	_nj_vertex_offset_;
extern	Int		_nj_depth_enable_;

extern  Int	volatile _nj_fatal_err_callback_;

/******************************/
/* Global Variable for Motion */
extern NJS_CAMERA _nj_motion_camera_;

/******************************/
/* Global Variable for Light  */

extern	NJS_LIGHT_MATERIAL		_nj_light_material_;/* the info.from Material */

/******************************/
/* Global Variable for Matrix */

extern Sint32   _nj_max_stack_size_;     /* Maximum Matrix Stack Size */
extern Sint32   _nj_stack_size_;         /* Number of Matrices pushed on the Stack */

extern NJS_MATRIX   _nj_unit_matrix_;

/*******************************/
/* Global Variable for Texture */
extern NJS_TEXLIST *_nj_current_texlist;        /* current texture list pointer */
extern NJS_TEXMEMLIST *_nj_texmemlist;          /* texture memory list pointer */
extern Uint32 _nj_texmemsize;                   /* texture momory list size */
extern Sint32 _nj_tex_count;
extern Uint32 _nj_current_texture;              /* current texture globalIndex */
extern Uint32 _nj_current_texture_bank;
extern char _nj_current_texture_path[256];

extern Uint32 _nj_tex_max_free_size;
extern Uint32 _nj_user_globalIndex;
extern Sint32 _nj_texglobal_color_;
extern NJS_TEXERRSTAT _nj_texerr_;
extern Int _nj_loadtexreq_mode_;
extern Int _nj_loadtexreq_i_;

extern Sint8	*_nj_texture_buffer_st;
extern Uint32 _nj_texture_buffer_max_size;
#endif
