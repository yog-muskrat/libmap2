
#ifndef MAPLIB_H
#define MAPLIB_H

#if defined(__BORLANDC__)
#ifndef MAPVERSN_H
  #include "mapversn.h"
#endif
#endif

#ifndef MAPSYST_H      
  #include "mapsyst.h"
#endif


#ifdef PANPROMPRJ

#define MAPEXE       "PROMGIS.EXE"
#define HELPNAMERU   "PROMGIS.HLP"
#define HELPNAMEENGL "PROMGIS.HLP"
#define INIFILE      "PROMGIS.INI"
#define PICFILE      "PROMGIS.PIC"

#define MTRLIB       "PROMMTR.DLL"
#define MTLLIB       "PROMMTL.DLL"
#define MAP43LIB     "PROMOLD.DLL"
#define MAPACCLIB    "PROMACC.DLL"

#define MAPTASKLIB   "PROMTSK.DLL"
#define MAPRUSLIB    "PROMRUS.DLL"
#define MAPENGLLIB   "PROMRUS.DLL"
#define MAPSELECLIB  "PROMSLC.DLL"
#define MAPOBJLIB    "PROMOBJ.DLL"
#define MAPVECTRLIB  "PROMVTR.DLL"
#define MAPPICTRLIB  "PROMPTR.DLL"
#define MAPVECEXLIB  "PROMVEX.DLL"
#define MAPPICEXLIB  "PROMPEX.DLL"
#define MAPPASPLIB   "PROMPSP.DLL"
#define MAPDBLIB     "PROMDB.DLL"
#define MAPTREELIB   "PROMTREE.DLL"
#define MAPCOMMLIB   "PROMCOM.DLL"
#define MAPCOMPLIB   "PROMCMP.DLL"
#define MAPEDITLIB   "PROMMED.DLL"
#define MAPRSWLIB    "PROMRSW.DLL"
#define MAPRSCLIB    "PROMRSC.DLL"
#define MAPLEGLIB    "PROMCLS.DLL"
#define MAPPRINTLIB  "PROMPRN.DLL"
#define MAPLISTLIB   "PROMLIST.DLL"

#else

#ifdef EDUCATION                      
#define MAPEXE       "MAPLIVE.EXE"    
#define HELPNAMERU   "MAPLIVE.HLP"    
#define HELPNAMEENGL "MAPLIVE.HLP"    
#define INIFILE      "MAPLIVE.INI"    
#define AXIAPILIB    "MAPLIVE.DLL"    
#else                                 

#ifdef PANVECTOR
#define MAPEXE       "VECTOR.EXE"
#define HELPNAMERU   "VECTOR.HLP"
#define HELPNAMEENGL "VECTOR.ENGL.HLP"     
#define INIFILE      "VECTOR.INI"
#define PICFILE      "VECTOR.PIC"
#define AXIAPILIB    "Panorama.DLL" 
#else

#ifdef MAP2005
#define HELPNAMERU    "Panorama.HLP" 
#define HELPNAMEENGL  "Panorama.ENGL.HLP" 
#define PICFILE       "Panorama.PIC" 
#define MAPTREE       "Panorama.TRE" 
#define AXIAPILIB     "Panorama.DLL" 
#define INIFILE       "Panorama.INI" 

#ifdef BUILD_FREE
 #define MAPEXE       "MAPFREE.EXE"
#else
#ifdef NAVIGATOR
 #define MAPEXE       "Navigator.exe" 
#else
 #define MAPEXE       "Panorama.exe"  
#endif
#endif
#else

#ifdef PANPROM

 #define MAPEXE       "PANPROM.EXE"
 #define AXIAPILIB    "PANPROM.DLL"
 #define INIFILE      "PANPROM.INI"
 #define HELPNAMERU   "PANORAMA.HLP"
 #define HELPNAMEENGL "PANORAMA.HLP"
 #define PICFILE      "PANORAMA.PIC"

#else
#ifdef PANEDIT
 #define MAPEXE       "PANEDIT.EXE"
 #define INIFILE      "PANEDIT.INI"
#define AXIAPILIB     "Panorama.DLL" 
#else
 #define MAPEXE       "Panorama.EXE"
 #define AXIAPILIB    "Panorama.DLL" 
#ifdef PANDEMO
 #define INIFILE      "PANDEMO.INI"
#else
 #define INIFILE      "PANORAMA.INI"
#endif
#endif

 #define HELPNAMERU   "PANORAMA.HLP"
 #define HELPNAMEENGL "PANORAMA.HLP"
 #define PICFILE      "PANORAMA.PIC"

#endif // TOPOGRAF
#endif // MAP2000
#endif
#endif

#if defined(__BORLANDC__) // Borland C++
  #define MTRLIB     "MAPMTREX.DLL"
  #define MTLBUILD   "MTLBUILD.DLL"       
  #define MAP43LIB   "MAPACC45.DLL"
  #define MAPACCLIB  "MAPACCES.DLL"
#else
  #define MTLLIB     "MTLAXSVC.DLL"
#ifndef LINUXAPI                          
  #define MAPACCLIB  "MAPAXSVC.DLL"
  #define MTRLIB     "MTRAXSVC.DLL"       
  #define MAP43LIB   "MAPACC45.DLL"
#else
  #define MAPACCLIB  "libmapacces.so"
  #define MTRLIB     "libmapmtrex.so"
  #define MAP43LIB   "libmapacc45.so"    
#endif
#endif

#ifdef WIN32API                            
#define MAPTASKLIB   "MAPTASK.DLL"
#define MAPSELECLIB  "MAPSELEC.DLL"        
#define MAPOBJLIB    "MAPOBJ.DLL"          
#else
#define MAPTASKLIB   "libmaptask.so"
#define MAPSELECLIB  "libmapselec.so"      
#define MAPOBJLIB    "libmapobj.so"        
#endif

#define MAPRUSLIB    "MAPRUS95.DLL"
#define MAPENGLLIB   "MAPENGL.DLL"
#define MAPENGLLIBX  "MAPENGLX.DLL"

#ifdef WIN32API                            
#define MAPPICTRLIB   "MAPPICTR.DLL"
#define MAPPASPLIB   "MAPPASP.DLL"
#define MAPSHP2MAPLIB "SHPTOMAP.DLL"       
#define MAP2SHPLIB    "MAPTOSHP.DLL"     
#else
#define MAPPICTRLIB   "libqtmappictr.so"
#define MAPPASPLIB    "libmappasp.so"
#define MAPSHP2MAPLIB "libshptomap.so"     
#define MAP2SHPLIB    "libmaptoshp.so"     
#define MAPWEBLIB     "libqtmapweb.so"
#endif

#define MAPTREELIB   "MAPTREE.DLL"

#ifdef WIN32API                            
#define MAPCOMMLIB   "MAPCOMM.DLL"
#define MAPEDITLIB   "MAPEDIT.DLL"
#define MAPCOMPLIB   "MAPCOMP.DLL"
#define MAPEDFRMLIB  "MAPEDFRM.DLL"
#define MAPDBLIB     "MAPDB.DLL"
#define MAPPICEXLIB  "MAPPICEX.DLL"      
#define MAPVECEXLIB  "MAPVECEX.DLL"
#define MAPRSCLIB    "RSCEDIT.DLL"       
#define MAP2MIFLIB    "MAPTOMIF.DLL"     
#define MAPMIF2MAPLIB "MIFTOMAP.DLL"      
#define MAPCNTEXLIB  "MAPCNTEX.DLL"
#define MAPVECTRLIB  "MAPVECTR.DLL"
#define MAPS572MAPLIB "S57TOMAP.DLL"      
#define MAPS57LIB     "MAPS57.DLL"        
#define MAPDGN2MAPLIB "DGNTOMAP.DLL"      
#define MAPDXF2MAPLIB "DXFTOMAP.DLL"      
#define PREPRINTLIB   "PREPRINT.DLL"      
#else
#define MAPEDITLIB   "libmapedits.so"
#define MAPCOMPLIB   "libmapcomp.so"      
#define MAPEDFRMLIB  "libmapedfrm.so"     
#define MAPCOMMLIB   "libmapcomm.so"      
#define MAPRCLIB     "libmaprc.so"        
#define MAPQTFRMLIB  "libmapqtfrm.so"     
#define MAPDBLIB     "libmapdb.so"        
#define MAPPICEXLIB  "libmappicex.so"     
#define MAPVECEXLIB  "libmapvecex.so"     
#define MAPRSCLIB    "librscedit.so"      
#define MAP2MIFLIB    "libmaptomif.so"    
#define MAPMIF2MAPLIB "libmiftomap.so"    
#define MAPCNTEXLIB   "libmapcntex.so"    
#define MAPVECTRLIB   "libmapvectr.so"    
#define MAPS572MAPLIB "libs57tomap.so"    
#define MAPS57LIB     "libs57tomap.so"        
#define MAPDXF2MAPLIB "libdxftomap.so"    
#define MAPDIRECTOR   "libdireditor.so"
#define MAPTINCREATOR "libtincreator.so"
#define PREPRINTLIB   "libpreprint.so"    
#endif

#define MAPRSWLIB    "RSWEDIT.DLL"

#define MAPLEGLIB    "MAPCLASS.DLL"
#define MAPPOINTLIB  "MAPPOINT.DLL"
#define MAPPRINTLIB  "MAPPRINT.DLL"
#define MAPLISTLIB   "MAPLIST.DLL"
#define MAPCONTRLIB  "MAPCONTR.DLL"       
#define MAPKWALIB    "MAPKWA.DLL"         
#define MAPTITLELIB  "MAPTITLE.DLL"       

#define MAPMAP2D14LIB "MAPTOD14.DLL"      
#define MAP2TIMLIB    "MAP2TIM.DLL"
#define JPG2RSWLIB    "JPG2RSW.DLL"       
#define RSWGISTLIB    "RSWGIST.DLL"       
#define MAPSCENALIB   "MAPSCENA.DLL"      
#define GEOEDITLIB    "GEOEDIT.DLL"       
#define MAP3DLIB      "MAP3D.DLL"         
#define MAPOBSETLIB   "MAPOBSET.DLL"      
#define GEOIMPRTLIB   "GEOIMPRT.DLL"      
#define MTR2TXTLIB    "MTR2TXT.DLL"       
#define GRDTOMTWLIB   "GRDTOMTW.DLL"      
#define GEOCODELIB    "GEOCODE.DLL"       
#define DBCREATELIB   "DBCREATE.DLL"      
#define CREATDIRLIB   "CREATDIR.DLL"      
#define GEODESYLIB    "GEODESY.DLL"       
#define GPSPROTCLIB   "GPSPROTC.DLL"      
#define TINBUILDLIB   "TINBUILD.DLL"      
#define GEOLOADLIB    "GEOLOAD.DLL"       
//#define PREPRINTLIB   "PREPRINT.DLL"      
#define GPSTESTLIB    "GPSTEST.DLL"       
#define RSCVIEWLIB    "RSCVIEW.DLL"       
#define CREATMTQLIB   "inclined.so"      
#define MTLZONELIB    "MTLZONE.DLL"
#define OBJNETLIB     "OBJNET.DLL"
#define ISOL2MTWLIB   "ISOL2MTW.DLL"
#define SRTM2MTWLIB   "SRTM2MTW.DLL"      
#define MTWCOMPLIB    "MTWCOMP.DLL"       
#define MTWADJUSLIB   "MTWADJUS.DLL"
#define MAPHYDROLIB   "MAPHYDRO.DLL"
#define MTWSUMLIB     "MTWSUM.DLL"
#define MTWCUTLIB     "MTWCUT.DLL"
#define MASSESLIB     "MASSES.DLL"

#endif

#endif // MAPLIB_H
 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
