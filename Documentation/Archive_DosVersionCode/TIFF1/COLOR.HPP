//--------------------------------------------------------//
//                                                        //
//   File:    COLOR.HPP                                   //
//                                                        //
//   Desc:    Classes for implementation of various       //
//            color models and their conversion.          //
//                                                        //
//--------------------------------------------------------//

#ifndef _COLOR_HPP_
#define _COLOR_HPP_

struct rgb;
struct cmy;
struct cmyk;

//...............an RGB class

struct rgb
{
   unsigned char red;
   unsigned char grn;
	unsigned char blu;

	rgb( )
	{
//## begin rgb::rgb%-2088149837.body preserve=yes
		red = grn = blu = 0;
	
//## end rgb::rgb%-2088149837.body
}
	rgb( int r, int g, int b )
	{
//## begin rgb::rgb%220995289.body preserve=yes
		red = r;
		grn = g;
		blu = b;
	
//## end rgb::rgb%220995289.body
}
	rgb( rgb& x )
	{
//## begin rgb::rgb%-933524090.body preserve=yes
		red = x.red;
		grn = x.grn;
		blu = x.blu;
	
//## end rgb::rgb%-933524090.body
}

	rgb( cmy& x );
   rgb( cmyk& x );
   unsigned char graylevel( void );
	void setrgb( unsigned char r, unsigned char g, unsigned char b );

	rgb& operator = ( rgb& x )
	{
//## begin rgb::operator =%1149479919.body preserve=yes
      red = x.red;
		grn = x.grn;
		blu = x.blu;
		return *this;
	
//## end rgb::operator =%1149479919.body
}
	rgb operator << ( int i )
	{
//## begin rgb::operator <<%-427714654.body preserve=yes
		rgb x( red<<i, grn<<i, blu<<i );
      return x;

//## end rgb::operator <<%-427714654.body
}
	rgb& operator <<= ( int i )
   {
//## begin rgb::operator <<=%-44904450.body preserve=yes
      red <<= i;
      grn <<= i;
      blu <<= i;
      return *this;

//## end rgb::operator <<=%-44904450.body
}
   rgb operator >> ( int i )
   {
//## begin rgb::operator >>%1573047929.body preserve=yes
      rgb x( red>>i, grn>>i, blu>>i );
      return x;
	
//## end rgb::operator >>%1573047929.body
}
	rgb& operator >>= ( int i )
	{
//## begin rgb::operator >>=%-1943942033.body preserve=yes
		red >>= i;
		grn >>= i;
		blu >>= i;
		return *this;
	
//## end rgb::operator >>=%-1943942033.body
}

};

//...............a CMY class

struct cmy
{
   unsigned char cyn;
   unsigned char mag;
   unsigned char yel;

   cmy( )
   {
//## begin cmy::cmy%-646092155.body preserve=yes
      cyn = mag = yel = 0;

//## end cmy::cmy%-646092155.body
}
   cmy( int c, int m, int y )
   {
//## begin cmy::cmy%-1989756853.body preserve=yes
      cyn = c;
      mag = m;
      yel = y;

//## end cmy::cmy%-1989756853.body
}
   cmy( cmy& x )
   {
//## begin cmy::cmy%172302647.body preserve=yes
      cyn = x.cyn;
      mag = x.mag;
      yel = x.yel;

//## end cmy::cmy%172302647.body
}

   cmy( rgb& x );
   cmy( cmyk& x );
   unsigned char graylevel( void );

   cmy& operator = ( cmy& x )
   {
//## begin cmy::operator =%-1249599255.body preserve=yes
      cyn = x.cyn;
      mag = x.mag;
      yel = x.yel;
      return *this;

//## end cmy::operator =%-1249599255.body
}
   cmy operator << ( int i )
   {
//## begin cmy::operator <<%606803080.body preserve=yes
      cmy x( cyn<<i, mag<<i, yel<<i );
      return x;

//## end cmy::operator <<%606803080.body
}
   cmy& operator <<= ( int i )
   {
//## begin cmy::operator <<=%1406285102.body preserve=yes
      cyn <<= i;
      mag <<= i;
      yel <<= i;
      return *this;

//## end cmy::operator <<=%1406285102.body
}
   cmy operator >> ( int i )
   {
//## begin cmy::operator >>%1743916022.body preserve=yes
      cmy x( cyn>>i, mag>>i, yel>>i );
      return x;

//## end cmy::operator >>%1743916022.body
}
   cmy& operator >>= ( int i )
   {
//## begin cmy::operator >>=%1834610559.body preserve=yes
      cyn >>= i;
      mag >>= i;
      yel >>= i;
      return *this;

//## end cmy::operator >>=%1834610559.body
}
};

//...............a CMYK class

struct cmyk
{
   unsigned char cyn;
   unsigned char mag;
   unsigned char yel;
   unsigned char blk;

   cmyk( )
   {
//## begin cmyk::cmyk%-2073644054.body preserve=yes
      cyn = mag = yel = blk = 0;

//## end cmyk::cmyk%-2073644054.body
}
   cmyk( int c, int y, int m, int k )
   {
//## begin cmyk::cmyk%1819723585.body preserve=yes
      cyn = c;
      mag = m;
      yel = y;
      blk = k;

//## end cmyk::cmyk%1819723585.body
}
   cmyk( cmyk& x )
   {
//## begin cmyk::cmyk%1165515595.body preserve=yes
      cyn = x.cyn;
      mag = x.mag;
      yel = x.yel;
      blk = x.blk;

//## end cmyk::cmyk%1165515595.body
}

   cmyk( rgb& x );
   cmyk( cmy& x );
   unsigned char graylevel( void );

   cmyk& operator = ( cmyk& x )
   {
//## begin cmyk::operator =%-2049096246.body preserve=yes
      cyn = x.cyn;
      mag = x.mag;
      yel = x.yel;
      blk = x.blk;
      return *this;

//## end cmyk::operator =%-2049096246.body
}
   cmyk operator << ( int i )
   {
//## begin cmyk::operator <<%-207700002.body preserve=yes
      cmyk x( cyn<<i, mag<<i, yel<<i, blk<<i );
      return x;

//## end cmyk::operator <<%-207700002.body
}
   cmyk& operator <<= ( int i )
   {
//## begin cmyk::operator <<=%1819352280.body preserve=yes
      cyn <<= i;
      mag <<= i;
      yel <<= i;
      blk <<= i;
      return *this;

//## end cmyk::operator <<=%1819352280.body
}
   cmyk operator >> ( int i )
   {
//## begin cmyk::operator >>%844933493.body preserve=yes
      cmyk x( cyn>>i, mag>>i, yel>>i, blk>>i );
      return x;

//## end cmyk::operator >>%844933493.body
}
   cmyk& operator >>= ( int i )
   {
//## begin cmyk::operator >>=%96310835.body preserve=yes
      cyn >>= i;
      mag >>= i;
      yel >>= i;
      blk >>= i;
      return *this;

//## end cmyk::operator >>=%96310835.body
}
};

//...............an RGB palette class

struct RgbPalette
{
   rgb *colors;
   int  ncolors;

   RgbPalette( )
   {
//## begin RgbPalette::RgbPalette%1305570414.body preserve=yes
      colors = 0;
      ncolors = 0;

//## end RgbPalette::RgbPalette%1305570414.body
}
   RgbPalette( rgb *clrs, int nclrs )
   {
//## begin RgbPalette::RgbPalette%566851428.body preserve=yes
      colors = clrs;
      ncolors = nclrs;

//## end RgbPalette::RgbPalette%566851428.body
}
  ~RgbPalette( )
   {
//## begin RgbPalette::~RgbPalette%-512965841.body preserve=yes

//## end RgbPalette::~RgbPalette%-512965841.body
}
};

#endif          
