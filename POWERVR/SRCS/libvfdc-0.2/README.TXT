
#     #  ###  ######   #######  #######
#     #   #   #     #  #        #     #
#     #   #   #     #  #        #     #
#     #   #   #     #  #####    #     #
 #   #    #   #     #  #        #     #
  # #     #   #     #  #        #     #
   #     ###  ######   #######  #######

							#######  #######  ######
							#        #     #  #     #
							#        #     #  #     #
							#####    #     #  ######
							#        #     #  #   #
							#        #     #  #    #
							#        #######  #     #

				######   ######   #######     #     #     #   #####      #      #####   #######
				#     #  #     #  #          # #    ##   ##  #     #    # #    #     #     #
				#     #  #     #  #         #   #   # # # #  #         #   #   #           #
				#     #  ######   #####    #     #  #  #  #  #        #     #   #####      #
				#     #  #   #    #        #######  #     #  #        #######        #     #
				#     #  #    #   #        #     #  #     #  #     #  #     #  #     #     #
				######   #     #  #######  #     #  #     #   #####   #     #   #####      #

														#     #		 ####           ###   
														#     #		#   ##         #   #  
														#     #		#  # #         #   #  
														#     #		# #  #            #   
														 #   #		##   #   ###     #    
														  # #		#    #   ###    #     
														   #		 ####    ###   #####  





I - Feature

	this lib work 4 KOS-1.1.7 or (greater)
	and can read the video format FLI / MPEG 1 & 2 / PSS (Playstation 2 format)  on DreamCast.
	Now you can add some FMV to your game
	
	FLIC : 
		use a resol 320x240 or 640x480 (a bit slow)

	MPEG  :
		use a resol 320x240 (a bit slow)
		no sound suport yet ... sorry 
		encode your video with : 
			Profile & level : MP@ML 
			Stream type     : System or Video (ES) 
			YUV format      : 4:2:0
			Bitrate			: <= 700
	PSS :
		PSS interleave an M2V and ADS sound , you can found around the web 
		some tool for encoding pss file.
		use a resol 320x240 
	

		 

II - Install

	go to the root of this package
	type "make" (this will create 2 lib in "lib" folder :  libfli.a & libmpg.a)

III - Use 

	See sample for how to use the lib ... it's very simple 
	the mpeg2 decoder need more memory space left than fli 


	
	
	