#
# Borland C++ IDE generated makefile
#
.AUTODEPEND


#
# Borland C++ tools
#
IMPLIB  = Implib
BCCD16     = Bcc +BccD16.cfg
TLINK   = TLink
TLIB    = TLib
TASM    = Tasm
#
# IDE macros
#


#
# Options
#
IDE_LFLAGSD16 =  -LC:\BC45\LIB
LLATD16_T3000dexe =  -v -Vt -LD:\BC45\LIB; -c -Gm -Txe
RLATD16_T3000dexe = 
BLATD16_T3000dexe = 
CNIEAT_T3000dexe = -ID:\BC45\INCLUDE;TIFF1 -DPANELSTATION;SERIAL_COMM;NET_BAC_COMM
LNIEAT_T3000dexe = -x
LEAT_T3000dexe = $(LLATD16_T3000dexe)
REAT_T3000dexe = $(RLATD16_T3000dexe)
BEAT_T3000dexe = $(BLATD16_T3000dexe)
CLATD16_mtkern1dcpp =  -v- -O-d -Z -Ol -Om -Op -Oi -Ov -Ob -O-e
LLATD16_mtkern1dcpp = 
RLATD16_mtkern1dcpp = 
BLATD16_mtkern1dcpp = 
CEAT_mtkern1dcpp = $(CEAT_T3000dexe) $(CLATD16_mtkern1dcpp)
CNIEAT_mtkern1dcpp = -ID:\BC45\INCLUDE;TIFF1 -DPANELSTATION;SERIAL_COMM;NET_BAC_COMM
LNIEAT_mtkern1dcpp = -x
LEAT_mtkern1dcpp = $(LEAT_T3000dexe) $(LLATD16_mtkern1dcpp)
REAT_mtkern1dcpp = $(REAT_T3000dexe) $(RLATD16_mtkern1dcpp)
BEAT_mtkern1dcpp = $(BEAT_T3000dexe) $(BLATD16_mtkern1dcpp)
CLATD16_mtkern2dcpp =  -f -v- -y- -zE_FARDATA -zFFAR_DATA -WXE -Z- -Op -O-d -Om -Oi -Ov -Ol
LLATD16_mtkern2dcpp = 
RLATD16_mtkern2dcpp = 
BLATD16_mtkern2dcpp = 
CEAT_mtkern2dcpp = $(CEAT_T3000dexe) $(CLATD16_mtkern2dcpp)
CNIEAT_mtkern2dcpp = -ID:\BC45\INCLUDE;TIFF1 -DPANELSTATION;SERIAL_COMM
LNIEAT_mtkern2dcpp = -x
LEAT_mtkern2dcpp = $(LEAT_T3000dexe) $(LLATD16_mtkern2dcpp)
REAT_mtkern2dcpp = $(REAT_T3000dexe) $(RLATD16_mtkern2dcpp)
BEAT_mtkern2dcpp = $(BEAT_T3000dexe) $(BLATD16_mtkern2dcpp)
CLATD16_maindcpp =  -v-
LLATD16_maindcpp = 
RLATD16_maindcpp = 
BLATD16_maindcpp = 
CEAT_maindcpp = $(CEAT_T3000dexe) $(CLATD16_maindcpp)
CNIEAT_maindcpp = -ID:\BC45\INCLUDE;TIFF1 -DPANELSTATION;SERIAL_COMM;NET_BAC_COMM
LNIEAT_maindcpp = -x
LEAT_maindcpp = $(LEAT_T3000dexe) $(LLATD16_maindcpp)
REAT_maindcpp = $(REAT_T3000dexe) $(RLATD16_maindcpp)
BEAT_maindcpp = $(BEAT_T3000dexe) $(BLATD16_maindcpp)
CLATD16_t3000dcpp =  -v -Ol -Ob -Om -Op -Ov -Z- -O-
LLATD16_t3000dcpp = 
RLATD16_t3000dcpp = 
BLATD16_t3000dcpp = 
CEAT_t3000dcpp = $(CEAT_T3000dexe) $(CLATD16_t3000dcpp)
CNIEAT_t3000dcpp = -ID:\BC45\INCLUDE;TIFF1 -DPANELSTATION;SERIAL_COMM;NET_BAC_COMM
LNIEAT_t3000dcpp = -x
LEAT_t3000dcpp = $(LEAT_T3000dexe) $(LLATD16_t3000dcpp)
REAT_t3000dcpp = $(REAT_T3000dexe) $(RLATD16_t3000dcpp)
BEAT_t3000dcpp = $(BEAT_T3000dexe) $(BLATD16_t3000dcpp)
CLATD16_ptpdcpp =  -v-
LLATD16_ptpdcpp = 
RLATD16_ptpdcpp = 
BLATD16_ptpdcpp = 
CEAT_ptpdcpp = $(CEAT_T3000dexe) $(CLATD16_ptpdcpp)
CNIEAT_ptpdcpp = -ID:\BC45\INCLUDE;TIFF1 -DPANELSTATION;SERIAL_COMM;NET_BAC_COMM
LNIEAT_ptpdcpp = -x
LEAT_ptpdcpp = $(LEAT_T3000dexe) $(LLATD16_ptpdcpp)
REAT_ptpdcpp = $(REAT_T3000dexe) $(RLATD16_ptpdcpp)
BEAT_ptpdcpp = $(BEAT_T3000dexe) $(BLATD16_ptpdcpp)
CLATD16_routerdcpp =  -v -Om -Op -Ov -Z -Ol -Ob
LLATD16_routerdcpp = 
RLATD16_routerdcpp = 
BLATD16_routerdcpp = 
CEAT_routerdcpp = $(CEAT_T3000dexe) $(CLATD16_routerdcpp)
CNIEAT_routerdcpp = -ID:\BC45\INCLUDE;TIFF1 -DPANELSTATION;SERIAL_COMM;NET_BAC_COMM
LNIEAT_routerdcpp = -x
LEAT_routerdcpp = $(LEAT_T3000dexe) $(LLATD16_routerdcpp)
REAT_routerdcpp = $(REAT_T3000dexe) $(RLATD16_routerdcpp)
BEAT_routerdcpp = $(BEAT_T3000dexe) $(BLATD16_routerdcpp)
CLATD16_projdcpp =  -Z -O -Ol -Ob -Om -Op -Ov -O-d -v
LLATD16_projdcpp = 
RLATD16_projdcpp = 
BLATD16_projdcpp = 
CEAT_projdcpp = $(CEAT_T3000dexe) $(CLATD16_projdcpp)
CNIEAT_projdcpp = -ID:\BC45\INCLUDE;TIFF1 -DPANELSTATION;SERIAL_COMM;NET_BAC_COMM
LNIEAT_projdcpp = -x
LEAT_projdcpp = $(LEAT_T3000dexe) $(LLATD16_projdcpp)
REAT_projdcpp = $(REAT_T3000dexe) $(RLATD16_projdcpp)
BEAT_projdcpp = $(BEAT_T3000dexe) $(BLATD16_projdcpp)
CLATD16_mstpdcpp =  -v- -O-d -Z -Ol -Ob -Om -Op -Ov -O- -O-i
LLATD16_mstpdcpp = 
RLATD16_mstpdcpp = 
BLATD16_mstpdcpp = 
CEAT_mstpdcpp = $(CEAT_T3000dexe) $(CLATD16_mstpdcpp)
CNIEAT_mstpdcpp = -ID:\BC45\INCLUDE;TIFF1 -DPANELSTATION;SERIAL_COMM;NET_BAC_COMM
LNIEAT_mstpdcpp = -x
LEAT_mstpdcpp = $(LEAT_T3000dexe) $(LLATD16_mstpdcpp)
REAT_mstpdcpp = $(REAT_T3000dexe) $(RLATD16_mstpdcpp)
BEAT_mstpdcpp = $(BEAT_T3000dexe) $(BLATD16_mstpdcpp)
CLATD16_dialdcpp =  -v- -Om -Op -Ov -O-c -Z- -O -Ol -Ob
LLATD16_dialdcpp = 
RLATD16_dialdcpp = 
BLATD16_dialdcpp = 
CEAT_dialdcpp = $(CEAT_T3000dexe) $(CLATD16_dialdcpp)
CNIEAT_dialdcpp = -ID:\BC45\INCLUDE;TIFF1 -DPANELSTATION;SERIAL_COMM;NET_BAC_COMM
LNIEAT_dialdcpp = -x
LEAT_dialdcpp = $(LEAT_T3000dexe) $(LLATD16_dialdcpp)
REAT_dialdcpp = $(REAT_T3000dexe) $(RLATD16_dialdcpp)
BEAT_dialdcpp = $(BEAT_T3000dexe) $(BLATD16_dialdcpp)
CLATD16_ggriddcpp =  -v- -Z -O -O-e -Ol -Ob -Om -Op -Ov -Os -O-d
LLATD16_ggriddcpp = 
RLATD16_ggriddcpp = 
BLATD16_ggriddcpp = 
CEAT_ggriddcpp = $(CEAT_T3000dexe) $(CLATD16_ggriddcpp)
CNIEAT_ggriddcpp = -ID:\BC45\INCLUDE;TIFF1 -DPANELSTATION;SERIAL_COMM;NET_BAC_COMM
LNIEAT_ggriddcpp = -x
LEAT_ggriddcpp = $(LEAT_T3000dexe) $(LLATD16_ggriddcpp)
REAT_ggriddcpp = $(REAT_T3000dexe) $(RLATD16_ggriddcpp)
BEAT_ggriddcpp = $(BEAT_T3000dexe) $(BLATD16_ggriddcpp)
CLATD16_serialdcpp =  -v- -Om -Op -Ov -O -Ol -Ob -Z-
LLATD16_serialdcpp = 
RLATD16_serialdcpp = 
BLATD16_serialdcpp = 
CEAT_serialdcpp = $(CEAT_T3000dexe) $(CLATD16_serialdcpp)
CNIEAT_serialdcpp = -ID:\BC45\INCLUDE;TIFF1 -DPANELSTATION;SERIAL_COMM;NET_BAC_COMM
LNIEAT_serialdcpp = -x
LEAT_serialdcpp = $(LEAT_T3000dexe) $(LLATD16_serialdcpp)
REAT_serialdcpp = $(REAT_T3000dexe) $(RLATD16_serialdcpp)
BEAT_serialdcpp = $(BEAT_T3000dexe) $(BLATD16_serialdcpp)
CLATD16_datedcpp = 
LLATD16_datedcpp = 
RLATD16_datedcpp = 
BLATD16_datedcpp = 
CEAT_datedcpp = $(CEAT_T3000dexe) $(CLATD16_datedcpp)
CNIEAT_datedcpp = -ID:\BC45\INCLUDE;TIFF1 -DPANELSTATION;SERIAL_COMM;NET_BAC_COMM
LNIEAT_datedcpp = -x
LEAT_datedcpp = $(LEAT_T3000dexe) $(LLATD16_datedcpp)
REAT_datedcpp = $(REAT_T3000dexe) $(RLATD16_datedcpp)
BEAT_datedcpp = $(BEAT_T3000dexe) $(BLATD16_datedcpp)
CLATD16_tiff1bimgviewrdcpp =  -v- -Om -Op -Ov -Z -O -Ol -Ob -O-d
LLATD16_tiff1bimgviewrdcpp = 
RLATD16_tiff1bimgviewrdcpp = 
BLATD16_tiff1bimgviewrdcpp = 
CEAT_tiff1bimgviewrdcpp = $(CEAT_T3000dexe) $(CLATD16_tiff1bimgviewrdcpp)
CNIEAT_tiff1bimgviewrdcpp = -ID:\BC45\INCLUDE;TIFF1 -DPANELSTATION;SERIAL_COMM;NET_BAC_COMM
LNIEAT_tiff1bimgviewrdcpp = -x
LEAT_tiff1bimgviewrdcpp = $(LEAT_T3000dexe) $(LLATD16_tiff1bimgviewrdcpp)
REAT_tiff1bimgviewrdcpp = $(REAT_T3000dexe) $(RLATD16_tiff1bimgviewrdcpp)
BEAT_tiff1bimgviewrdcpp = $(BEAT_T3000dexe) $(BLATD16_tiff1bimgviewrdcpp)
CLATD16_tiff1bvga12dasm = 
LLATD16_tiff1bvga12dasm = 
RLATD16_tiff1bvga12dasm = 
BLATD16_tiff1bvga12dasm = 
CEAT_tiff1bvga12dasm = $(CEAT_T3000dexe) $(CLATD16_tiff1bvga12dasm)
CNIEAT_tiff1bvga12dasm = -ID:\BC45\INCLUDE;TIFF1 -DPANELSTATION;SERIAL_COMM;NET_BAC_COMM
LNIEAT_tiff1bvga12dasm = -x
LEAT_tiff1bvga12dasm = $(LEAT_T3000dexe) $(LLATD16_tiff1bvga12dasm)
REAT_tiff1bvga12dasm = $(REAT_T3000dexe) $(RLATD16_tiff1bvga12dasm)
BEAT_tiff1bvga12dasm = $(BEAT_T3000dexe) $(BLATD16_tiff1bvga12dasm)
CLATD16_tiff1bwrttifdcpp =  -O-d -Om -Op -Ov -Z -O -Ol -Ob
LLATD16_tiff1bwrttifdcpp = 
RLATD16_tiff1bwrttifdcpp = 
BLATD16_tiff1bwrttifdcpp = 
CEAT_tiff1bwrttifdcpp = $(CEAT_T3000dexe) $(CLATD16_tiff1bwrttifdcpp)
CNIEAT_tiff1bwrttifdcpp = -ID:\BC45\INCLUDE;TIFF1 -DPANELSTATION;SERIAL_COMM;NET_BAC_COMM
LNIEAT_tiff1bwrttifdcpp = -x
LEAT_tiff1bwrttifdcpp = $(LEAT_T3000dexe) $(LLATD16_tiff1bwrttifdcpp)
REAT_tiff1bwrttifdcpp = $(REAT_T3000dexe) $(RLATD16_tiff1bwrttifdcpp)
BEAT_tiff1bwrttifdcpp = $(BEAT_T3000dexe) $(BLATD16_tiff1bwrttifdcpp)
CLATD16_tiff1bvgapaldasm = 
LLATD16_tiff1bvgapaldasm = 
RLATD16_tiff1bvgapaldasm = 
BLATD16_tiff1bvgapaldasm = 
CEAT_tiff1bvgapaldasm = $(CEAT_T3000dexe) $(CLATD16_tiff1bvgapaldasm)
CNIEAT_tiff1bvgapaldasm = -ID:\BC45\INCLUDE;TIFF1 -DPANELSTATION;SERIAL_COMM;NET_BAC_COMM
LNIEAT_tiff1bvgapaldasm = -x
LEAT_tiff1bvgapaldasm = $(LEAT_T3000dexe) $(LLATD16_tiff1bvgapaldasm)
REAT_tiff1bvgapaldasm = $(REAT_T3000dexe) $(RLATD16_tiff1bvgapaldasm)
BEAT_tiff1bvgapaldasm = $(BEAT_T3000dexe) $(BLATD16_tiff1bvgapaldasm)
CLATD16_tiff1bvtifdcpp =  -v- -Om -Op -Ov -Ol -Ob -O -O-d
LLATD16_tiff1bvtifdcpp = 
RLATD16_tiff1bvtifdcpp = 
BLATD16_tiff1bvtifdcpp = 
CEAT_tiff1bvtifdcpp = $(CEAT_T3000dexe) $(CLATD16_tiff1bvtifdcpp)
CNIEAT_tiff1bvtifdcpp = -ID:\BC45\INCLUDE;TIFF1 -DPANELSTATION;SERIAL_COMM;NET_BAC_COMM
LNIEAT_tiff1bvtifdcpp = -x
LEAT_tiff1bvtifdcpp = $(LEAT_T3000dexe) $(LLATD16_tiff1bvtifdcpp)
REAT_tiff1bvtifdcpp = $(REAT_T3000dexe) $(RLATD16_tiff1bvtifdcpp)
BEAT_tiff1bvtifdcpp = $(BEAT_T3000dexe) $(BLATD16_tiff1bvtifdcpp)
CLATD16_tiff1btifcodecdcpp =  -v- -Om -Op -Ov -Z- -Ol -Ob -O-d -O
LLATD16_tiff1btifcodecdcpp = 
RLATD16_tiff1btifcodecdcpp = 
BLATD16_tiff1btifcodecdcpp = 
CEAT_tiff1btifcodecdcpp = $(CEAT_T3000dexe) $(CLATD16_tiff1btifcodecdcpp)
CNIEAT_tiff1btifcodecdcpp = -ID:\BC45\INCLUDE;TIFF1 -DPANELSTATION;SERIAL_COMM;NET_BAC_COMM
LNIEAT_tiff1btifcodecdcpp = -x
LEAT_tiff1btifcodecdcpp = $(LEAT_T3000dexe) $(LLATD16_tiff1btifcodecdcpp)
REAT_tiff1btifcodecdcpp = $(REAT_T3000dexe) $(RLATD16_tiff1btifcodecdcpp)
BEAT_tiff1btifcodecdcpp = $(BEAT_T3000dexe) $(BLATD16_tiff1btifcodecdcpp)
CLATD16_tiff1btifdcpp =  -v- -Om -Op -Ov -Z -O -Ol -Ob -O-d
LLATD16_tiff1btifdcpp = 
RLATD16_tiff1btifdcpp = 
BLATD16_tiff1btifdcpp = 
CEAT_tiff1btifdcpp = $(CEAT_T3000dexe) $(CLATD16_tiff1btifdcpp)
CNIEAT_tiff1btifdcpp = -ID:\BC45\INCLUDE;TIFF1 -DPANELSTATION;SERIAL_COMM;NET_BAC_COMM
LNIEAT_tiff1btifdcpp = -x
LEAT_tiff1btifdcpp = $(LEAT_T3000dexe) $(LLATD16_tiff1btifdcpp)
REAT_tiff1btifdcpp = $(REAT_T3000dexe) $(RLATD16_tiff1btifdcpp)
BEAT_tiff1btifdcpp = $(BEAT_T3000dexe) $(BLATD16_tiff1btifdcpp)
CLATD16_tiff1brevbytedcpp =  -O-d -Z -O -Ol -Ob -Om -Op -Ov
LLATD16_tiff1brevbytedcpp = 
RLATD16_tiff1brevbytedcpp = 
BLATD16_tiff1brevbytedcpp = 
CEAT_tiff1brevbytedcpp = $(CEAT_T3000dexe) $(CLATD16_tiff1brevbytedcpp)
CNIEAT_tiff1brevbytedcpp = -ID:\BC45\INCLUDE;TIFF1 -DPANELSTATION;SERIAL_COMM;NET_BAC_COMM
LNIEAT_tiff1brevbytedcpp = -x
LEAT_tiff1brevbytedcpp = $(LEAT_T3000dexe) $(LLATD16_tiff1brevbytedcpp)
REAT_tiff1brevbytedcpp = $(REAT_T3000dexe) $(RLATD16_tiff1brevbytedcpp)
BEAT_tiff1brevbytedcpp = $(BEAT_T3000dexe) $(BLATD16_tiff1brevbytedcpp)
CLATD16_tiff1bintenmapdcpp =  -Om -Op -Ov -Z -O -Ol -Ob -O-d
LLATD16_tiff1bintenmapdcpp = 
RLATD16_tiff1bintenmapdcpp = 
BLATD16_tiff1bintenmapdcpp = 
CEAT_tiff1bintenmapdcpp = $(CEAT_T3000dexe) $(CLATD16_tiff1bintenmapdcpp)
CNIEAT_tiff1bintenmapdcpp = -ID:\BC45\INCLUDE;TIFF1 -DPANELSTATION;SERIAL_COMM;NET_BAC_COMM
LNIEAT_tiff1bintenmapdcpp = -x
LEAT_tiff1bintenmapdcpp = $(LEAT_T3000dexe) $(LLATD16_tiff1bintenmapdcpp)
REAT_tiff1bintenmapdcpp = $(REAT_T3000dexe) $(RLATD16_tiff1bintenmapdcpp)
BEAT_tiff1bintenmapdcpp = $(BEAT_T3000dexe) $(BLATD16_tiff1bintenmapdcpp)
CLATD16_tiff1bimgstoredcpp =  -v- -O-d -Z -O -Ol -Ob -Om -Op -Ov
LLATD16_tiff1bimgstoredcpp = 
RLATD16_tiff1bimgstoredcpp = 
BLATD16_tiff1bimgstoredcpp = 
CEAT_tiff1bimgstoredcpp = $(CEAT_T3000dexe) $(CLATD16_tiff1bimgstoredcpp)
CNIEAT_tiff1bimgstoredcpp = -ID:\BC45\INCLUDE;TIFF1 -DPANELSTATION;SERIAL_COMM;NET_BAC_COMM
LNIEAT_tiff1bimgstoredcpp = -x
LEAT_tiff1bimgstoredcpp = $(LEAT_T3000dexe) $(LLATD16_tiff1bimgstoredcpp)
REAT_tiff1bimgstoredcpp = $(REAT_T3000dexe) $(RLATD16_tiff1bimgstoredcpp)
BEAT_tiff1bimgstoredcpp = $(BEAT_T3000dexe) $(BLATD16_tiff1bimgstoredcpp)
CLATD16_tiff1bditherdcpp =  -Om -Op -Ov -Z -O -Ol -Ob -O-d
LLATD16_tiff1bditherdcpp = 
RLATD16_tiff1bditherdcpp = 
BLATD16_tiff1bditherdcpp = 
CEAT_tiff1bditherdcpp = $(CEAT_T3000dexe) $(CLATD16_tiff1bditherdcpp)
CNIEAT_tiff1bditherdcpp = -ID:\BC45\INCLUDE;TIFF1 -DPANELSTATION;SERIAL_COMM;NET_BAC_COMM
LNIEAT_tiff1bditherdcpp = -x
LEAT_tiff1bditherdcpp = $(LEAT_T3000dexe) $(LLATD16_tiff1bditherdcpp)
REAT_tiff1bditherdcpp = $(REAT_T3000dexe) $(RLATD16_tiff1bditherdcpp)
BEAT_tiff1bditherdcpp = $(BEAT_T3000dexe) $(BLATD16_tiff1bditherdcpp)
CLATD16_tiff1bdisplaydcpp =  -O-d -Z -O -Ol -Ob -Om -Op -Ov -v-
LLATD16_tiff1bdisplaydcpp = 
RLATD16_tiff1bdisplaydcpp = 
BLATD16_tiff1bdisplaydcpp = 
CEAT_tiff1bdisplaydcpp = $(CEAT_T3000dexe) $(CLATD16_tiff1bdisplaydcpp)
CNIEAT_tiff1bdisplaydcpp = -ID:\BC45\INCLUDE;TIFF1 -DPANELSTATION;SERIAL_COMM;NET_BAC_COMM
LNIEAT_tiff1bdisplaydcpp = -x
LEAT_tiff1bdisplaydcpp = $(LEAT_T3000dexe) $(LLATD16_tiff1bdisplaydcpp)
REAT_tiff1bdisplaydcpp = $(REAT_T3000dexe) $(RLATD16_tiff1bdisplaydcpp)
BEAT_tiff1bdisplaydcpp = $(BEAT_T3000dexe) $(BLATD16_tiff1bdisplaydcpp)
CLATD16_tiff1bcolormapdcpp =  -Om -Op -Ov -Z -O -Ol -Ob -O-d
LLATD16_tiff1bcolormapdcpp = 
RLATD16_tiff1bcolormapdcpp = 
BLATD16_tiff1bcolormapdcpp = 
CEAT_tiff1bcolormapdcpp = $(CEAT_T3000dexe) $(CLATD16_tiff1bcolormapdcpp)
CNIEAT_tiff1bcolormapdcpp = -ID:\BC45\INCLUDE;TIFF1 -DPANELSTATION;SERIAL_COMM;NET_BAC_COMM
LNIEAT_tiff1bcolormapdcpp = -x
LEAT_tiff1bcolormapdcpp = $(LEAT_T3000dexe) $(LLATD16_tiff1bcolormapdcpp)
REAT_tiff1bcolormapdcpp = $(REAT_T3000dexe) $(RLATD16_tiff1bcolormapdcpp)
BEAT_tiff1bcolormapdcpp = $(BEAT_T3000dexe) $(BLATD16_tiff1bcolormapdcpp)
CLATD16_tiff1bcolordcpp =  -O-d -Z -O -Ol -Ob -Om -Op -Ov
LLATD16_tiff1bcolordcpp = 
RLATD16_tiff1bcolordcpp = 
BLATD16_tiff1bcolordcpp = 
CEAT_tiff1bcolordcpp = $(CEAT_T3000dexe) $(CLATD16_tiff1bcolordcpp)
CNIEAT_tiff1bcolordcpp = -ID:\BC45\INCLUDE;TIFF1 -DPANELSTATION;SERIAL_COMM;NET_BAC_COMM
LNIEAT_tiff1bcolordcpp = -x
LEAT_tiff1bcolordcpp = $(LEAT_T3000dexe) $(LLATD16_tiff1bcolordcpp)
REAT_tiff1bcolordcpp = $(REAT_T3000dexe) $(RLATD16_tiff1bcolordcpp)
BEAT_tiff1bcolordcpp = $(BEAT_T3000dexe) $(BLATD16_tiff1bcolordcpp)
CLATD16_groupdcpp =  -v -Z- -O -O-e -Ol -Ob -Os -Om -Op -Ov -O-d
LLATD16_groupdcpp = 
RLATD16_groupdcpp = 
BLATD16_groupdcpp = 
CEAT_groupdcpp = $(CEAT_T3000dexe) $(CLATD16_groupdcpp)
CNIEAT_groupdcpp = -ID:\BC45\INCLUDE;TIFF1 -DPANELSTATION;SERIAL_COMM;NET_BAC_COMM
LNIEAT_groupdcpp = -x
LEAT_groupdcpp = $(LEAT_T3000dexe) $(LLATD16_groupdcpp)
REAT_groupdcpp = $(REAT_T3000dexe) $(RLATD16_groupdcpp)
BEAT_groupdcpp = $(BEAT_T3000dexe) $(BLATD16_groupdcpp)
CLATD16_rs232dcpp =  -v- -Om -Op -Ov -Z -Ol -Ob -O-d -O
LLATD16_rs232dcpp = 
RLATD16_rs232dcpp = 
BLATD16_rs232dcpp = 
CEAT_rs232dcpp = $(CEAT_T3000dexe) $(CLATD16_rs232dcpp)
CNIEAT_rs232dcpp = -ID:\BC45\INCLUDE;TIFF1 -DPANELSTATION;SERIAL_COMM;NET_BAC_COMM
LNIEAT_rs232dcpp = -x
LEAT_rs232dcpp = $(LEAT_T3000dexe) $(LLATD16_rs232dcpp)
REAT_rs232dcpp = $(REAT_T3000dexe) $(RLATD16_rs232dcpp)
BEAT_rs232dcpp = $(BEAT_T3000dexe) $(BLATD16_rs232dcpp)
CLATD16_queuedcpp =  -Om -Op -Ov -O -Ol -Ob
LLATD16_queuedcpp = 
RLATD16_queuedcpp = 
BLATD16_queuedcpp = 
CEAT_queuedcpp = $(CEAT_T3000dexe) $(CLATD16_queuedcpp)
CNIEAT_queuedcpp = -ID:\BC45\INCLUDE;TIFF1 -DPANELSTATION;SERIAL_COMM;NET_BAC_COMM
LNIEAT_queuedcpp = -x
LEAT_queuedcpp = $(LEAT_T3000dexe) $(LLATD16_queuedcpp)
REAT_queuedcpp = $(REAT_T3000dexe) $(RLATD16_queuedcpp)
BEAT_queuedcpp = $(BEAT_T3000dexe) $(BLATD16_queuedcpp)
CLATD16_pcirq_ddcpp =  -v-
LLATD16_pcirq_ddcpp = 
RLATD16_pcirq_ddcpp = 
BLATD16_pcirq_ddcpp = 
CEAT_pcirq_ddcpp = $(CEAT_T3000dexe) $(CLATD16_pcirq_ddcpp)
CNIEAT_pcirq_ddcpp = -ID:\BC45\INCLUDE;TIFF1 -DPANELSTATION;SERIAL_COMM;NET_BAC_COMM
LNIEAT_pcirq_ddcpp = -x
LEAT_pcirq_ddcpp = $(LEAT_T3000dexe) $(LLATD16_pcirq_ddcpp)
REAT_pcirq_ddcpp = $(REAT_T3000dexe) $(RLATD16_pcirq_ddcpp)
BEAT_pcirq_ddcpp = $(BEAT_T3000dexe) $(BLATD16_pcirq_ddcpp)
CLATD16_pc8250dcpp =  -v- -O-d -Z -O -Ol -Ob -Om -Op -Ov
LLATD16_pc8250dcpp = 
RLATD16_pc8250dcpp = 
BLATD16_pc8250dcpp = 
CEAT_pc8250dcpp = $(CEAT_T3000dexe) $(CLATD16_pc8250dcpp)
CNIEAT_pc8250dcpp = -ID:\BC45\INCLUDE;TIFF1 -DPANELSTATION;SERIAL_COMM;NET_BAC_COMM
LNIEAT_pc8250dcpp = -x
LEAT_pc8250dcpp = $(LEAT_T3000dexe) $(LLATD16_pc8250dcpp)
REAT_pc8250dcpp = $(REAT_T3000dexe) $(RLATD16_pc8250dcpp)
BEAT_pc8250dcpp = $(BEAT_T3000dexe) $(BLATD16_pc8250dcpp)
CLATD16_modemdcpp =  -v- -O-d -Z- -O -Ol -Ob -Om -Op -Ov
LLATD16_modemdcpp = 
RLATD16_modemdcpp = 
BLATD16_modemdcpp = 
CEAT_modemdcpp = $(CEAT_T3000dexe) $(CLATD16_modemdcpp)
CNIEAT_modemdcpp = -ID:\BC45\INCLUDE;TIFF1 -DPANELSTATION;SERIAL_COMM;NET_BAC_COMM
LNIEAT_modemdcpp = -x
LEAT_modemdcpp = $(LEAT_T3000dexe) $(LLATD16_modemdcpp)
REAT_modemdcpp = $(REAT_T3000dexe) $(RLATD16_modemdcpp)
BEAT_modemdcpp = $(BEAT_T3000dexe) $(BLATD16_modemdcpp)
CLATD16_isr_8250dcpp =  -O-d -Om -Op -Oi -Ov -v- -Z -Ol -Ob -Oc -Oe
LLATD16_isr_8250dcpp = 
RLATD16_isr_8250dcpp = 
BLATD16_isr_8250dcpp = 
CEAT_isr_8250dcpp = $(CEAT_T3000dexe) $(CLATD16_isr_8250dcpp)
CNIEAT_isr_8250dcpp = -ID:\BC45\INCLUDE;TIFF1 -DPANELSTATION;SERIAL_COMM;NET_BAC_COMM
LNIEAT_isr_8250dcpp = -x
LEAT_isr_8250dcpp = $(LEAT_T3000dexe) $(LLATD16_isr_8250dcpp)
REAT_isr_8250dcpp = $(REAT_T3000dexe) $(RLATD16_isr_8250dcpp)
BEAT_isr_8250dcpp = $(BEAT_T3000dexe) $(BLATD16_isr_8250dcpp)
CLATD16_crcdcpp =  -Om -Op -Oi -Ov -Z -Ol -O -Ob -O-d
LLATD16_crcdcpp = 
RLATD16_crcdcpp = 
BLATD16_crcdcpp = 
CEAT_crcdcpp = $(CEAT_T3000dexe) $(CLATD16_crcdcpp)
CNIEAT_crcdcpp = -ID:\BC45\INCLUDE;TIFF1 -DPANELSTATION;SERIAL_COMM;NET_BAC_COMM
LNIEAT_crcdcpp = -x
LEAT_crcdcpp = $(LEAT_T3000dexe) $(LLATD16_crcdcpp)
REAT_crcdcpp = $(REAT_T3000dexe) $(RLATD16_crcdcpp)
BEAT_crcdcpp = $(BEAT_T3000dexe) $(BLATD16_crcdcpp)
CLATD16_msdosdcpp =  -v- -O-d -Z -O -Ol -Ob -Om -Op -Ov
LLATD16_msdosdcpp = 
RLATD16_msdosdcpp = 
BLATD16_msdosdcpp = 
CEAT_msdosdcpp = $(CEAT_T3000dexe) $(CLATD16_msdosdcpp)
CNIEAT_msdosdcpp = -ID:\BC45\INCLUDE;TIFF1 -DPANELSTATION;SERIAL_COMM;NET_BAC_COMM
LNIEAT_msdosdcpp = -x
LEAT_msdosdcpp = $(LEAT_T3000dexe) $(LLATD16_msdosdcpp)
REAT_msdosdcpp = $(REAT_T3000dexe) $(RLATD16_msdosdcpp)
BEAT_msdosdcpp = $(BEAT_T3000dexe) $(BLATD16_msdosdcpp)
CLATD16_exprdcpp =  -O-d -Z -O -Ol -Ob -Om -Op -Ov -v-
LLATD16_exprdcpp = 
RLATD16_exprdcpp = 
BLATD16_exprdcpp = 
CEAT_exprdcpp = $(CEAT_T3000dexe) $(CLATD16_exprdcpp)
CNIEAT_exprdcpp = -ID:\BC45\INCLUDE;TIFF1 -DPANELSTATION;SERIAL_COMM;NET_BAC_COMM
LNIEAT_exprdcpp = -x
LEAT_exprdcpp = $(LEAT_T3000dexe) $(LLATD16_exprdcpp)
REAT_exprdcpp = $(REAT_T3000dexe) $(RLATD16_exprdcpp)
BEAT_exprdcpp = $(BEAT_T3000dexe) $(BLATD16_exprdcpp)
CLATD16_littlecdcpp =  -v- -Op -Om -Ov -Z -O -Ol -Ob -O-d
LLATD16_littlecdcpp = 
RLATD16_littlecdcpp = 
BLATD16_littlecdcpp = 
CEAT_littlecdcpp = $(CEAT_T3000dexe) $(CLATD16_littlecdcpp)
CNIEAT_littlecdcpp = -ID:\BC45\INCLUDE;TIFF1 -DPANELSTATION;SERIAL_COMM;NET_BAC_COMM
LNIEAT_littlecdcpp = -x
LEAT_littlecdcpp = $(LEAT_T3000dexe) $(LLATD16_littlecdcpp)
REAT_littlecdcpp = $(REAT_T3000dexe) $(RLATD16_littlecdcpp)
BEAT_littlecdcpp = $(BEAT_T3000dexe) $(BLATD16_littlecdcpp)
CLATD16_parserdcpp =  -v- -O-d -Z -O -Ol -Ob -Om -Op -Ov
LLATD16_parserdcpp = 
RLATD16_parserdcpp = 
BLATD16_parserdcpp = 
CEAT_parserdcpp = $(CEAT_T3000dexe) $(CLATD16_parserdcpp)
CNIEAT_parserdcpp = -ID:\BC45\INCLUDE;TIFF1 -DPANELSTATION;SERIAL_COMM;NET_BAC_COMM
LNIEAT_parserdcpp = -x
LEAT_parserdcpp = $(LEAT_T3000dexe) $(LLATD16_parserdcpp)
REAT_parserdcpp = $(REAT_T3000dexe) $(RLATD16_parserdcpp)
BEAT_parserdcpp = $(BEAT_T3000dexe) $(BLATD16_parserdcpp)
CLATD16_ggraphdcpp =  -v -Om -O-i -Op -Ov -Ol -Ob -Z- -O -O-d -O-W
LLATD16_ggraphdcpp = 
RLATD16_ggraphdcpp = 
BLATD16_ggraphdcpp = 
CEAT_ggraphdcpp = $(CEAT_T3000dexe) $(CLATD16_ggraphdcpp)
CNIEAT_ggraphdcpp = -ID:\BC45\INCLUDE;TIFF1 -DPANELSTATION;SERIAL_COMM;NET_BAC_COMM
LNIEAT_ggraphdcpp = -x
LEAT_ggraphdcpp = $(LEAT_T3000dexe) $(LLATD16_ggraphdcpp)
REAT_ggraphdcpp = $(REAT_T3000dexe) $(RLATD16_ggraphdcpp)
BEAT_ggraphdcpp = $(BEAT_T3000dexe) $(BLATD16_ggraphdcpp)
CLATD16_gmbardcpp =  -v- -Z- -O -Oe -Ol -Ob -Om -O-d -Op -Ov
LLATD16_gmbardcpp = 
RLATD16_gmbardcpp = 
BLATD16_gmbardcpp = 
CEAT_gmbardcpp = $(CEAT_T3000dexe) $(CLATD16_gmbardcpp)
CNIEAT_gmbardcpp = -ID:\BC45\INCLUDE;TIFF1 -DPANELSTATION;SERIAL_COMM;NET_BAC_COMM
LNIEAT_gmbardcpp = -x
LEAT_gmbardcpp = $(LEAT_T3000dexe) $(LLATD16_gmbardcpp)
REAT_gmbardcpp = $(REAT_T3000dexe) $(RLATD16_gmbardcpp)
BEAT_gmbardcpp = $(BEAT_T3000dexe) $(BLATD16_gmbardcpp)
CLATD16_gviewdcpp =  -v- -Z- -O -O-e -Ol -Ob -Om -Op -Ov -O-d -OW
LLATD16_gviewdcpp = 
RLATD16_gviewdcpp = 
BLATD16_gviewdcpp = 
CEAT_gviewdcpp = $(CEAT_T3000dexe) $(CLATD16_gviewdcpp)
CNIEAT_gviewdcpp = -ID:\BC45\INCLUDE;TIFF1 -DPANELSTATION;SERIAL_COMM;NET_BAC_COMM
LNIEAT_gviewdcpp = -x
LEAT_gviewdcpp = $(LEAT_T3000dexe) $(LLATD16_gviewdcpp)
REAT_gviewdcpp = $(REAT_T3000dexe) $(RLATD16_gviewdcpp)
BEAT_gviewdcpp = $(BEAT_T3000dexe) $(BLATD16_gviewdcpp)
CLATD16_gwindcpp =  -v -Z- -O -O-e -Ol -Ob -O-W -Om -Op -Ov -O-d
LLATD16_gwindcpp = 
RLATD16_gwindcpp = 
BLATD16_gwindcpp = 
CEAT_gwindcpp = $(CEAT_T3000dexe) $(CLATD16_gwindcpp)
CNIEAT_gwindcpp = -ID:\BC45\INCLUDE;TIFF1 -DPANELSTATION;NETWORK_COMM;
LNIEAT_gwindcpp = -x
LEAT_gwindcpp = $(LEAT_T3000dexe) $(LLATD16_gwindcpp)
REAT_gwindcpp = $(REAT_T3000dexe) $(RLATD16_gwindcpp)
BEAT_gwindcpp = $(BEAT_T3000dexe) $(BLATD16_gwindcpp)
CLATD16_geditdcpp =  -v- -O -Ol -Ob -Om -Op -Ov -O-d -Z
LLATD16_geditdcpp = 
RLATD16_geditdcpp = 
BLATD16_geditdcpp = 
CEAT_geditdcpp = $(CEAT_T3000dexe) $(CLATD16_geditdcpp)
CNIEAT_geditdcpp = -ID:\BC45\INCLUDE;TIFF1 -DPANELSTATION;SERIAL_COMM;NET_BAC_COMM
LNIEAT_geditdcpp = -x
LEAT_geditdcpp = $(LEAT_T3000dexe) $(LLATD16_geditdcpp)
REAT_geditdcpp = $(REAT_T3000dexe) $(RLATD16_geditdcpp)
BEAT_geditdcpp = $(BEAT_T3000dexe) $(BLATD16_geditdcpp)
CLATD16_gedit1dcpp =  -v-
LLATD16_gedit1dcpp = 
RLATD16_gedit1dcpp = 
BLATD16_gedit1dcpp = 
CEAT_gedit1dcpp = $(CEAT_T3000dexe) $(CLATD16_gedit1dcpp)
CNIEAT_gedit1dcpp = -ID:\BC45\INCLUDE;TIFF1 -DPANELSTATION;SERIAL_COMM;NET_BAC_COMM
LNIEAT_gedit1dcpp = -x
LEAT_gedit1dcpp = $(LEAT_T3000dexe) $(LLATD16_gedit1dcpp)
REAT_gedit1dcpp = $(REAT_T3000dexe) $(RLATD16_gedit1dcpp)
BEAT_gedit1dcpp = $(BEAT_T3000dexe) $(BLATD16_gedit1dcpp)
CLATD16_pointcldcpp =  -v -Z- -O -O-e -Ol -Ob -Om -Op -Ov -O-d -O-W -y-
LLATD16_pointcldcpp = 
RLATD16_pointcldcpp = 
BLATD16_pointcldcpp = 
CEAT_pointcldcpp = $(CEAT_T3000dexe) $(CLATD16_pointcldcpp)
CNIEAT_pointcldcpp = -ID:\BC45\INCLUDE;TIFF1 -DPANELSTATION;SERIAL_COMM;NET_BAC_COMM
LNIEAT_pointcldcpp = -x
LEAT_pointcldcpp = $(LEAT_T3000dexe) $(LLATD16_pointcldcpp)
REAT_pointcldcpp = $(REAT_T3000dexe) $(RLATD16_pointcldcpp)
BEAT_pointcldcpp = $(BEAT_T3000dexe) $(BLATD16_pointcldcpp)
CLATD16_alarmdcpp =  -v- -Z- -O -O-e -Ol -Ob -O-d -Om -Op -Ov
LLATD16_alarmdcpp = 
RLATD16_alarmdcpp = 
BLATD16_alarmdcpp = 
CEAT_alarmdcpp = $(CEAT_T3000dexe) $(CLATD16_alarmdcpp)
CNIEAT_alarmdcpp = -ID:\BC45\INCLUDE;TIFF1 -DPANELSTATION;SERIAL_COMM;NET_BAC_COMM
LNIEAT_alarmdcpp = -x
LEAT_alarmdcpp = $(LEAT_T3000dexe) $(LLATD16_alarmdcpp)
REAT_alarmdcpp = $(REAT_T3000dexe) $(RLATD16_alarmdcpp)
BEAT_alarmdcpp = $(BEAT_T3000dexe) $(BLATD16_alarmdcpp)
CLATD16_mousedcpp =  -v- -y- -k- -N- -WXE -O -Ol -Ob -Om -Op -Ov
LLATD16_mousedcpp = 
RLATD16_mousedcpp = 
BLATD16_mousedcpp = 
CEAT_mousedcpp = $(CEAT_T3000dexe) $(CLATD16_mousedcpp)
CNIEAT_mousedcpp = -ID:\BC45\INCLUDE;TIFF1 -DPANELSTATION;NETWORK_COMM;
LNIEAT_mousedcpp = -x
LEAT_mousedcpp = $(LEAT_T3000dexe) $(LLATD16_mousedcpp)
REAT_mousedcpp = $(REAT_T3000dexe) $(RLATD16_mousedcpp)
BEAT_mousedcpp = $(BEAT_T3000dexe) $(BLATD16_mousedcpp)
CLATD16_new1dcpp =  -v- -O-d -Om -Op -Oi -Ov -Z -Ol -O- -Ob
LLATD16_new1dcpp = 
RLATD16_new1dcpp = 
BLATD16_new1dcpp = 
CEAT_new1dcpp = $(CEAT_T3000dexe) $(CLATD16_new1dcpp)
CNIEAT_new1dcpp = -ID:\BC45\INCLUDE;TIFF1 -DPANELSTATION;SERIAL_COMM;NET_BAC_COMM
LNIEAT_new1dcpp = -x
LEAT_new1dcpp = $(LEAT_T3000dexe) $(LLATD16_new1dcpp)
REAT_new1dcpp = $(REAT_T3000dexe) $(RLATD16_new1dcpp)
BEAT_new1dcpp = $(BEAT_T3000dexe) $(BLATD16_new1dcpp)
CLATD16_new2dcpp =  -v-
LLATD16_new2dcpp = 
RLATD16_new2dcpp = 
BLATD16_new2dcpp = 
CEAT_new2dcpp = $(CEAT_T3000dexe) $(CLATD16_new2dcpp)
CNIEAT_new2dcpp = -ID:\BC45\INCLUDE;TIFF1 -DPANELSTATION;SERIAL_COMM;NET_BAC_COMM
LNIEAT_new2dcpp = -x
LEAT_new2dcpp = $(LEAT_T3000dexe) $(LLATD16_new2dcpp)
REAT_new2dcpp = $(REAT_T3000dexe) $(RLATD16_new2dcpp)
BEAT_new2dcpp = $(BEAT_T3000dexe) $(BLATD16_new2dcpp)
CLATD16_ipxdcpp =  -v
LLATD16_ipxdcpp = 
RLATD16_ipxdcpp = 
BLATD16_ipxdcpp = 
CEAT_ipxdcpp = $(CEAT_T3000dexe) $(CLATD16_ipxdcpp)
CNIEAT_ipxdcpp = -ID:\BC45\INCLUDE;TIFF1 -DPANELSTATION;SERIAL_COMM;NET_BAC_COMM
LNIEAT_ipxdcpp = -x
LEAT_ipxdcpp = $(LEAT_T3000dexe) $(LLATD16_ipxdcpp)
REAT_ipxdcpp = $(REAT_T3000dexe) $(RLATD16_ipxdcpp)
BEAT_ipxdcpp = $(BEAT_T3000dexe) $(BLATD16_ipxdcpp)
CLATD16_net_bacdcpp =  -v
LLATD16_net_bacdcpp = 
RLATD16_net_bacdcpp = 
BLATD16_net_bacdcpp = 
CEAT_net_bacdcpp = $(CEAT_T3000dexe) $(CLATD16_net_bacdcpp)
CNIEAT_net_bacdcpp = -ID:\BC45\INCLUDE;TIFF1 -DPANELSTATION;SERIAL_COMM;NET_BAC_COMM
LNIEAT_net_bacdcpp = -x
LEAT_net_bacdcpp = $(LEAT_T3000dexe) $(LLATD16_net_bacdcpp)
REAT_net_bacdcpp = $(REAT_T3000dexe) $(RLATD16_net_bacdcpp)
BEAT_net_bacdcpp = $(BEAT_T3000dexe) $(BLATD16_net_bacdcpp)
CLATD16_net_asmdcpp =  -v-
LLATD16_net_asmdcpp = 
RLATD16_net_asmdcpp = 
BLATD16_net_asmdcpp = 
CEAT_net_asmdcpp = $(CEAT_T3000dexe) $(CLATD16_net_asmdcpp)
CNIEAT_net_asmdcpp = -ID:\BC45\INCLUDE;TIFF1 -DPANELSTATION;SERIAL_COMM;NET_BAC_COMM
LNIEAT_net_asmdcpp = -x
LEAT_net_asmdcpp = $(LEAT_T3000dexe) $(LLATD16_net_asmdcpp)
REAT_net_asmdcpp = $(REAT_T3000dexe) $(RLATD16_net_asmdcpp)
BEAT_net_asmdcpp = $(BEAT_T3000dexe) $(BLATD16_net_asmdcpp)
CLATD16_execdcpp =  -v- -Om -Op -O-i -Ov -Ol -Ob -O-d -Z- -O -O-W
LLATD16_execdcpp = 
RLATD16_execdcpp = 
BLATD16_execdcpp = 
CEAT_execdcpp = $(CEAT_T3000dexe) $(CLATD16_execdcpp)
CNIEAT_execdcpp = -ID:\BC45\INCLUDE;TIFF1 -DPANELSTATION;SERIAL_COMM;NET_BAC_COMM
LNIEAT_execdcpp = -x
LEAT_execdcpp = $(LEAT_T3000dexe) $(LLATD16_execdcpp)
REAT_execdcpp = $(REAT_T3000dexe) $(RLATD16_execdcpp)
BEAT_execdcpp = $(BEAT_T3000dexe) $(BLATD16_execdcpp)
CLATD16_virtualdcpp =  -v- -O-d -Om -Op -Oi -Ov -Z -Ol -A-
LLATD16_virtualdcpp = 
RLATD16_virtualdcpp = 
BLATD16_virtualdcpp = 
CEAT_virtualdcpp = $(CEAT_T3000dexe) $(CLATD16_virtualdcpp)
CNIEAT_virtualdcpp = -ID:\BC45\INCLUDE;TIFF1 -DPANELSTATION;SERIAL_COMM;NET_BAC_COMM
LNIEAT_virtualdcpp = -x
LEAT_virtualdcpp = $(LEAT_T3000dexe) $(LLATD16_virtualdcpp)
REAT_virtualdcpp = $(REAT_T3000dexe) $(RLATD16_virtualdcpp)
BEAT_virtualdcpp = $(BEAT_T3000dexe) $(BLATD16_virtualdcpp)
CLATD16_othersdcpp =  -v- -Z -Ol -Ob -Om -Op -Ov
LLATD16_othersdcpp = 
RLATD16_othersdcpp = 
BLATD16_othersdcpp = 
CEAT_othersdcpp = $(CEAT_T3000dexe) $(CLATD16_othersdcpp)
CNIEAT_othersdcpp = -ID:\BC45\INCLUDE;TIFF1 -DPANELSTATION;SERIAL_COMM;NET_BAC_COMM
LNIEAT_othersdcpp = -x
LEAT_othersdcpp = $(LEAT_T3000dexe) $(LLATD16_othersdcpp)
REAT_othersdcpp = $(REAT_T3000dexe) $(RLATD16_othersdcpp)
BEAT_othersdcpp = $(BEAT_T3000dexe) $(BLATD16_othersdcpp)
CLATD16_netstatdcpp =  -v-
LLATD16_netstatdcpp = 
RLATD16_netstatdcpp = 
BLATD16_netstatdcpp = 
CEAT_netstatdcpp = $(CEAT_T3000dexe) $(CLATD16_netstatdcpp)
CNIEAT_netstatdcpp = -ID:\BC45\INCLUDE;TIFF1 -DPANELSTATION;SERIAL_COMM;NET_BAC_COMM
LNIEAT_netstatdcpp = -x
LEAT_netstatdcpp = $(LEAT_T3000dexe) $(LLATD16_netstatdcpp)
REAT_netstatdcpp = $(REAT_T3000dexe) $(RLATD16_netstatdcpp)
BEAT_netstatdcpp = $(BEAT_T3000dexe) $(BLATD16_netstatdcpp)

#
# Dependency List
#
Dep_t3000 = \
   T3000.exe

t3000 : BccD16.cfg $(Dep_t3000)
  echo MakeNode 

Dep_T3000dexe = \
   OBJ\mtkern1.obj\
   OBJ\mtkern2.obj\
   OBJ\main.obj\
   OBJ\t3000.obj\
   OBJ\ptp.obj\
   OBJ\router.obj\
   OBJ\proj.obj\
   OBJ\mstp.obj\
   OBJ\dial.obj\
   OBJ\ggrid.obj\
   OBJ\serial.obj\
   OBJ\date.obj\
   litt.obj\
   OBJ\vga13.obj\
   OBJ\vmode.obj\
   OBJ\imgviewr.obj\
   OBJ\dist3.obj\
   OBJ\xms.obj\
   OBJ\ems.obj\
   OBJ\vga12.obj\
   OBJ\wrttif.obj\
   OBJ\vgaquery.obj\
   OBJ\revword.obj\
   OBJ\vgapal.obj\
   OBJ\iscale.obj\
   OBJ\ati62.obj\
   OBJ\vtif.obj\
   OBJ\tifcodec.obj\
   OBJ\tif.obj\
   OBJ\revbyte.obj\
   OBJ\intenmap.obj\
   OBJ\imgstore.obj\
   OBJ\dither.obj\
   OBJ\display.obj\
   OBJ\colormap.obj\
   OBJ\color.obj\
   OBJ\group.obj\
   OBJ\rs232.obj\
   OBJ\queue.obj\
   OBJ\pcirq_d.obj\
   OBJ\pc8250.obj\
   OBJ\modem.obj\
   OBJ\isr_8250.obj\
   OBJ\crc.obj\
   proj.def\
   egavga.obj\
   herc.obj\
   OBJ\fxengine.obj\
   OBJ\msdos.obj\
   OBJ\expr.obj\
   OBJ\littlec.obj\
   OBJ\parser.obj\
   OBJ\ggraph.obj\
   OBJ\gmbar.obj\
   OBJ\gview.obj\
   OBJ\gwin.obj\
   OBJ\gedit.obj\
   OBJ\gedit1.obj\
   OBJ\pointcl.obj\
   OBJ\alarm.obj\
   OBJ\mouse.obj\
   OBJ\new1.obj\
   OBJ\new2.obj\
   OBJ\packbs.obj\
   OBJ\ipx.obj\
   OBJ\net_bac.obj\
   OBJ\net_asm.obj\
   OBJ\exec.obj\
   OBJ\virtual.obj\
   OBJ\t3000hlp.obj\
   OBJ\others.obj\
   OBJ\netstat.obj

T3000.exe : $(Dep_T3000dexe)
  $(TLINK) @&&|
 /v $(IDE_LFLAGSD16) $(LEAT_T3000dexe) $(LNIEAT_T3000dexe) +
D:\BC45\LIB\c0x.obj+
OBJ\mtkern1.obj+
OBJ\mtkern2.obj+
OBJ\main.obj+
OBJ\t3000.obj+
OBJ\ptp.obj+
OBJ\router.obj+
OBJ\proj.obj+
OBJ\mstp.obj+
OBJ\dial.obj+
OBJ\ggrid.obj+
OBJ\serial.obj+
OBJ\date.obj+
litt.obj+
OBJ\vga13.obj+
OBJ\vmode.obj+
OBJ\imgviewr.obj+
OBJ\dist3.obj+
OBJ\xms.obj+
OBJ\ems.obj+
OBJ\vga12.obj+
OBJ\wrttif.obj+
OBJ\vgaquery.obj+
OBJ\revword.obj+
OBJ\vgapal.obj+
OBJ\iscale.obj+
OBJ\ati62.obj+
OBJ\vtif.obj+
OBJ\tifcodec.obj+
OBJ\tif.obj+
OBJ\revbyte.obj+
OBJ\intenmap.obj+
OBJ\imgstore.obj+
OBJ\dither.obj+
OBJ\display.obj+
OBJ\colormap.obj+
OBJ\color.obj+
OBJ\group.obj+
OBJ\rs232.obj+
OBJ\queue.obj+
OBJ\pcirq_d.obj+
OBJ\pc8250.obj+
OBJ\modem.obj+
OBJ\isr_8250.obj+
OBJ\crc.obj+
egavga.obj+
herc.obj+
OBJ\fxengine.obj+
OBJ\msdos.obj+
OBJ\expr.obj+
OBJ\littlec.obj+
OBJ\parser.obj+
OBJ\ggraph.obj+
OBJ\gmbar.obj+
OBJ\gview.obj+
OBJ\gwin.obj+
OBJ\gedit.obj+
OBJ\gedit1.obj+
OBJ\pointcl.obj+
OBJ\alarm.obj+
OBJ\mouse.obj+
OBJ\new1.obj+
OBJ\new2.obj+
OBJ\packbs.obj+
OBJ\ipx.obj+
OBJ\net_bac.obj+
OBJ\net_asm.obj+
OBJ\exec.obj+
OBJ\virtual.obj+
OBJ\t3000hlp.obj+
OBJ\others.obj+
OBJ\netstat.obj
$<,$*
D:\BC45\LIB\dpmi16.lib+
D:\BC45\LIB\emux.lib+
D:\BC45\LIB\mathwl.lib+
D:\BC45\LIB\bgi16.lib+
D:\BC45\LIB\cwl.lib
proj.def
|

OBJ\mtkern1.obj :  mtkern1.cpp
  $(BCCD16) -c @&&|
 $(CEAT_mtkern1dcpp) $(CNIEAT_mtkern1dcpp) -o$@ mtkern1.cpp
|

OBJ\mtkern2.obj :  mtkern2.cpp
  $(BCCD16) -c @&&|
 $(CEAT_mtkern2dcpp) $(CNIEAT_mtkern2dcpp) -o$@ mtkern2.cpp
|

OBJ\main.obj :  main.cpp
  $(BCCD16) -c @&&|
 $(CEAT_maindcpp) $(CNIEAT_maindcpp) -o$@ main.cpp
|

OBJ\t3000.obj :  t3000.cpp
  $(BCCD16) -c @&&|
 $(CEAT_t3000dcpp) $(CNIEAT_t3000dcpp) -o$@ t3000.cpp
|

OBJ\ptp.obj :  ptp.cpp
  $(BCCD16) -c @&&|
 $(CEAT_ptpdcpp) $(CNIEAT_ptpdcpp) -o$@ ptp.cpp
|

OBJ\router.obj :  router.cpp
  $(BCCD16) -c @&&|
 $(CEAT_routerdcpp) $(CNIEAT_routerdcpp) -o$@ router.cpp
|

OBJ\proj.obj :  proj.cpp
  $(BCCD16) -c @&&|
 $(CEAT_projdcpp) $(CNIEAT_projdcpp) -o$@ proj.cpp
|

OBJ\mstp.obj :  mstp.cpp
  $(BCCD16) -c @&&|
 $(CEAT_mstpdcpp) $(CNIEAT_mstpdcpp) -o$@ mstp.cpp
|

OBJ\dial.obj :  dial.cpp
  $(BCCD16) -c @&&|
 $(CEAT_dialdcpp) $(CNIEAT_dialdcpp) -o$@ dial.cpp
|

OBJ\ggrid.obj :  ggrid.cpp
  $(BCCD16) -c @&&|
 $(CEAT_ggriddcpp) $(CNIEAT_ggriddcpp) -o$@ ggrid.cpp
|

OBJ\serial.obj :  serial.cpp
  $(BCCD16) -c @&&|
 $(CEAT_serialdcpp) $(CNIEAT_serialdcpp) -o$@ serial.cpp
|

OBJ\date.obj :  date.cpp
  $(BCCD16) -c @&&|
 $(CEAT_datedcpp) $(CNIEAT_datedcpp) -o$@ date.cpp
|

OBJ\vga13.obj :  tiff1\vga13.asm
  $(TASM) @&&|
 /ml D:\BC45\TEMCOAPP\T3000_~1\tiff1\vga13.asm ,OBJ\vga13.obj
|

OBJ\vmode.obj :  tiff1\vmode.asm
  $(TASM) @&&|
 /ml D:\BC45\TEMCOAPP\T3000_~1\tiff1\vmode.asm ,OBJ\vmode.obj
|

OBJ\imgviewr.obj :  tiff1\imgviewr.cpp
  $(BCCD16) -c @&&|
 $(CEAT_tiff1bimgviewrdcpp) $(CNIEAT_tiff1bimgviewrdcpp) -o$@ tiff1\imgviewr.cpp
|

OBJ\dist3.obj :  tiff1\dist3.asm
  $(TASM) @&&|
 /ml D:\BC45\TEMCOAPP\T3000_~1\tiff1\dist3.asm ,OBJ\dist3.obj
|

OBJ\xms.obj :  tiff1\xms.asm
  $(TASM) @&&|
 /ml D:\BC45\TEMCOAPP\T3000_~1\tiff1\xms.asm ,OBJ\xms.obj
|

OBJ\ems.obj :  tiff1\ems.asm
  $(TASM) @&&|
 /ml D:\BC45\TEMCOAPP\T3000_~1\tiff1\ems.asm ,OBJ\ems.obj
|

OBJ\vga12.obj :  tiff1\vga12.asm
  $(TASM) @&&|
 /ml D:\BC45\TEMCOAPP\T3000_~1\tiff1\vga12.asm ,OBJ\vga12.obj
|

OBJ\wrttif.obj :  tiff1\wrttif.cpp
  $(BCCD16) -c @&&|
 $(CEAT_tiff1bwrttifdcpp) $(CNIEAT_tiff1bwrttifdcpp) -o$@ tiff1\wrttif.cpp
|

OBJ\vgaquery.obj :  tiff1\vgaquery.asm
  $(TASM) @&&|
 /ml D:\BC45\TEMCOAPP\T3000_~1\tiff1\vgaquery.asm ,OBJ\vgaquery.obj
|

OBJ\revword.obj :  tiff1\revword.asm
  $(TASM) @&&|
 /ml D:\BC45\TEMCOAPP\T3000_~1\tiff1\revword.asm ,OBJ\revword.obj
|

OBJ\vgapal.obj :  tiff1\vgapal.asm
  $(TASM) @&&|
 /ml D:\BC45\TEMCOAPP\T3000_~1\tiff1\vgapal.asm ,OBJ\vgapal.obj
|

OBJ\iscale.obj :  tiff1\iscale.asm
  $(TASM) @&&|
 /ml D:\BC45\TEMCOAPP\T3000_~1\tiff1\iscale.asm ,OBJ\iscale.obj
|

OBJ\ati62.obj :  tiff1\ati62.asm
  $(TASM) @&&|
 /ml D:\BC45\TEMCOAPP\T3000_~1\tiff1\ati62.asm ,OBJ\ati62.obj
|

OBJ\vtif.obj :  tiff1\vtif.cpp
  $(BCCD16) -c @&&|
 $(CEAT_tiff1bvtifdcpp) $(CNIEAT_tiff1bvtifdcpp) -o$@ tiff1\vtif.cpp
|

OBJ\tifcodec.obj :  tiff1\tifcodec.cpp
  $(BCCD16) -c @&&|
 $(CEAT_tiff1btifcodecdcpp) $(CNIEAT_tiff1btifcodecdcpp) -o$@ tiff1\tifcodec.cpp
|

OBJ\tif.obj :  tiff1\tif.cpp
  $(BCCD16) -c @&&|
 $(CEAT_tiff1btifdcpp) $(CNIEAT_tiff1btifdcpp) -o$@ tiff1\tif.cpp
|

OBJ\revbyte.obj :  tiff1\revbyte.cpp
  $(BCCD16) -c @&&|
 $(CEAT_tiff1brevbytedcpp) $(CNIEAT_tiff1brevbytedcpp) -o$@ tiff1\revbyte.cpp
|

OBJ\intenmap.obj :  tiff1\intenmap.cpp
  $(BCCD16) -c @&&|
 $(CEAT_tiff1bintenmapdcpp) $(CNIEAT_tiff1bintenmapdcpp) -o$@ tiff1\intenmap.cpp
|

OBJ\imgstore.obj :  tiff1\imgstore.cpp
  $(BCCD16) -c @&&|
 $(CEAT_tiff1bimgstoredcpp) $(CNIEAT_tiff1bimgstoredcpp) -o$@ tiff1\imgstore.cpp
|

OBJ\dither.obj :  tiff1\dither.cpp
  $(BCCD16) -c @&&|
 $(CEAT_tiff1bditherdcpp) $(CNIEAT_tiff1bditherdcpp) -o$@ tiff1\dither.cpp
|

OBJ\display.obj :  tiff1\display.cpp
  $(BCCD16) -c @&&|
 $(CEAT_tiff1bdisplaydcpp) $(CNIEAT_tiff1bdisplaydcpp) -o$@ tiff1\display.cpp
|

OBJ\colormap.obj :  tiff1\colormap.cpp
  $(BCCD16) -c @&&|
 $(CEAT_tiff1bcolormapdcpp) $(CNIEAT_tiff1bcolormapdcpp) -o$@ tiff1\colormap.cpp
|

OBJ\color.obj :  tiff1\color.cpp
  $(BCCD16) -c @&&|
 $(CEAT_tiff1bcolordcpp) $(CNIEAT_tiff1bcolordcpp) -o$@ tiff1\color.cpp
|

OBJ\group.obj :  group.cpp
  $(BCCD16) -c @&&|
 $(CEAT_groupdcpp) $(CNIEAT_groupdcpp) -o$@ group.cpp
|

OBJ\rs232.obj :  rs232.cpp
  $(BCCD16) -c @&&|
 $(CEAT_rs232dcpp) $(CNIEAT_rs232dcpp) -o$@ rs232.cpp
|

OBJ\queue.obj :  queue.cpp
  $(BCCD16) -c @&&|
 $(CEAT_queuedcpp) $(CNIEAT_queuedcpp) -o$@ queue.cpp
|

OBJ\pcirq_d.obj :  pcirq_d.cpp
  $(BCCD16) -c @&&|
 $(CEAT_pcirq_ddcpp) $(CNIEAT_pcirq_ddcpp) -o$@ pcirq_d.cpp
|

OBJ\pc8250.obj :  pc8250.cpp
  $(BCCD16) -c @&&|
 $(CEAT_pc8250dcpp) $(CNIEAT_pc8250dcpp) -o$@ pc8250.cpp
|

OBJ\modem.obj :  modem.cpp
  $(BCCD16) -c @&&|
 $(CEAT_modemdcpp) $(CNIEAT_modemdcpp) -o$@ modem.cpp
|

OBJ\isr_8250.obj :  isr_8250.cpp
  $(BCCD16) -c @&&|
 $(CEAT_isr_8250dcpp) $(CNIEAT_isr_8250dcpp) -o$@ isr_8250.cpp
|

OBJ\crc.obj :  crc.cpp
  $(BCCD16) -c @&&|
 $(CEAT_crcdcpp) $(CNIEAT_crcdcpp) -o$@ crc.cpp
|

OBJ\fxengine.obj :  fxengine.cpp
  $(BCCD16) -c @&&|
 $(CEAT_T3000dexe) $(CNIEAT_T3000dexe) -o$@ fxengine.cpp
|

OBJ\msdos.obj :  msdos.cpp
  $(BCCD16) -c @&&|
 $(CEAT_msdosdcpp) $(CNIEAT_msdosdcpp) -o$@ msdos.cpp
|

OBJ\expr.obj :  expr.cpp
  $(BCCD16) -c @&&|
 $(CEAT_exprdcpp) $(CNIEAT_exprdcpp) -o$@ expr.cpp
|

OBJ\littlec.obj :  littlec.cpp
  $(BCCD16) -c @&&|
 $(CEAT_littlecdcpp) $(CNIEAT_littlecdcpp) -o$@ littlec.cpp
|

OBJ\parser.obj :  parser.cpp
  $(BCCD16) -c @&&|
 $(CEAT_parserdcpp) $(CNIEAT_parserdcpp) -o$@ parser.cpp
|

OBJ\ggraph.obj :  ggraph.cpp
  $(BCCD16) -c @&&|
 $(CEAT_ggraphdcpp) $(CNIEAT_ggraphdcpp) -o$@ ggraph.cpp
|

OBJ\gmbar.obj :  gmbar.cpp
  $(BCCD16) -c @&&|
 $(CEAT_gmbardcpp) $(CNIEAT_gmbardcpp) -o$@ gmbar.cpp
|

OBJ\gview.obj :  gview.cpp
  $(BCCD16) -c @&&|
 $(CEAT_gviewdcpp) $(CNIEAT_gviewdcpp) -o$@ gview.cpp
|

OBJ\gwin.obj :  gwin.cpp
  $(BCCD16) -c @&&|
 $(CEAT_gwindcpp) $(CNIEAT_gwindcpp) -o$@ gwin.cpp
|

OBJ\gedit.obj :  gedit.cpp
  $(BCCD16) -c @&&|
 $(CEAT_geditdcpp) $(CNIEAT_geditdcpp) -o$@ gedit.cpp
|

OBJ\gedit1.obj :  gedit1.cpp
  $(BCCD16) -c @&&|
 $(CEAT_gedit1dcpp) $(CNIEAT_gedit1dcpp) -o$@ gedit1.cpp
|

OBJ\pointcl.obj :  pointcl.cpp
  $(BCCD16) -c @&&|
 $(CEAT_pointcldcpp) $(CNIEAT_pointcldcpp) -o$@ pointcl.cpp
|

OBJ\alarm.obj :  alarm.cpp
  $(BCCD16) -c @&&|
 $(CEAT_alarmdcpp) $(CNIEAT_alarmdcpp) -o$@ alarm.cpp
|

OBJ\mouse.obj :  mouse.cpp
  $(BCCD16) -c @&&|
 $(CEAT_mousedcpp) $(CNIEAT_mousedcpp) -o$@ mouse.cpp
|

OBJ\new1.obj :  new1.cpp
  $(BCCD16) -c @&&|
 $(CEAT_new1dcpp) $(CNIEAT_new1dcpp) -o$@ new1.cpp
|

OBJ\new2.obj :  new2.cpp
  $(BCCD16) -c @&&|
 $(CEAT_new2dcpp) $(CNIEAT_new2dcpp) -o$@ new2.cpp
|

OBJ\packbs.obj :  packbs.cpp
  $(BCCD16) -c @&&|
 $(CEAT_T3000dexe) $(CNIEAT_T3000dexe) -o$@ packbs.cpp
|

OBJ\ipx.obj :  ipx.cpp
  $(BCCD16) -c @&&|
 $(CEAT_ipxdcpp) $(CNIEAT_ipxdcpp) -o$@ ipx.cpp
|

OBJ\net_bac.obj :  net_bac.cpp
  $(BCCD16) -c @&&|
 $(CEAT_net_bacdcpp) $(CNIEAT_net_bacdcpp) -o$@ net_bac.cpp
|

OBJ\net_asm.obj :  net_asm.cpp
  $(BCCD16) -c @&&|
 $(CEAT_net_asmdcpp) $(CNIEAT_net_asmdcpp) -o$@ net_asm.cpp
|

OBJ\exec.obj :  exec.cpp
  $(BCCD16) -c @&&|
 $(CEAT_execdcpp) $(CNIEAT_execdcpp) -o$@ exec.cpp
|

OBJ\virtual.obj :  virtual.cpp
  $(BCCD16) -c @&&|
 $(CEAT_virtualdcpp) $(CNIEAT_virtualdcpp) -o$@ virtual.cpp
|

OBJ\t3000hlp.obj :  t3000hlp.cpp
  $(BCCD16) -c @&&|
 $(CEAT_T3000dexe) $(CNIEAT_T3000dexe) -o$@ t3000hlp.cpp
|

OBJ\others.obj :  others.cpp
  $(BCCD16) -c @&&|
 $(CEAT_othersdcpp) $(CNIEAT_othersdcpp) -o$@ others.cpp
|

OBJ\netstat.obj :  netstat.cpp
  $(BCCD16) -c @&&|
 $(CEAT_netstatdcpp) $(CNIEAT_netstatdcpp) -o$@ netstat.cpp
|

# Compiler configuration file
BccD16.cfg : 
   Copy &&|
-ml
-R
-v
-vi
-H
-H=proj.csm
-4
-R
-3
-K
-g150
-i32
-v
-O-
-O-m
-O-l
-O-b
-Z-
-k
-rd
-vi-
-ml
-Ot
-Ff-
-Ff=10000
-dc-
-h-
-O-p
-O-i
-WXE
-f
-ff-
-Od
-x-
-C-
-H=
-Hu
-RT
-y
-N
| $@


