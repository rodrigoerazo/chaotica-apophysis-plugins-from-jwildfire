/*
    Apophysis Plugin

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

/*
    This 3D plugin written by
	Larry Berlin
	September 2009
	http://apophysisrevealed.com
	Recommended Usage: Intended to "pop" flat transforms into a shape away from the XY plane.
	Once a shape exists, other 3D plugins can better operate as they should.
*/

typedef struct
{                       
  
} Variables;

#include "apoplugin.h"

// Set the name of this plugin
APO_PLUGIN("inflateZ_6");

// Define the Variables
APO_VARIABLES(

);

// You must call the argument "vp".
int PluginVarPrepare(Variation* vp)
{

  return TRUE; // Always return TRUE.    

}

// You must call the argument "vp".
int PluginVarCalc(Variation* vp)
{
  double ang, kik, adf;
 
  ang = atan2(FTy,FTx);
  adf = FTy - FTx;
  kik = ang * sin(adf);
  FPz += VVAR * (1.5 - acos(sin(ang) * kik * 0.5));           
  
  return TRUE; // Always return TRUE.    

}
