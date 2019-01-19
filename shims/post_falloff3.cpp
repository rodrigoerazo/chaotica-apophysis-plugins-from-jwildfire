/*
    Apophysis Plugin: post_falloff3

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/PostFalloff3Func.java

    Automatically converted by @mwegner

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

#include "datahelpers.h"

typedef struct
{

    int ___warning;
} Variables;

#define APO_VARIABLE_PREFIX "post_falloff3_"
#include "plugin.h"

APO_PLUGIN("post_falloff3");
APO_VARIABLES(

    { "WARNING_this_plugin_does_nothing", INTEGER, OFFSET(___warning), 0, 1, 0 },
);


int PluginVarPrepare(Variation* vp)
{
    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    return TRUE;
}





// original java file embedded here:
//
// /*
//   JWildfire - an image and animation processor written in Java 
//   Copyright (C) 1995-2011 Andreas Maschke
// 
//   This is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser 
//   General Public License as published by the Free Software Foundation; either version 2.1 of the 
//   License, or (at your option) any later version.
//  
//   This software is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without 
//   even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
//   Lesser General Public License for more details.
// 
//   You should have received a copy of the GNU Lesser General Public License along with this software; 
//   if not, write to the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
//   02110-1301 USA, or see the FSF site: http://www.fsf.org.
// */
// package org.jwildfire.create.tina.variation;
// 
// import org.jwildfire.create.tina.base.XYZPoint;
// 
// public class PostFalloff3Func extends AbstractFalloff3Func {
//   private static final long serialVersionUID = 1L;
// 
//   @Override
//   public String getName() {
//     return "post_falloff3";
//   }
// 
//   @Override
//   protected void applyVOut(XYZPoint pAffineTP, XYZPoint pVarTP, Double4 pVOut, double pWeight) {
//     pVarTP.x = pVOut.x * pWeight;
//     pVarTP.y = pVOut.y * pWeight;
//     pVarTP.z = pVOut.z * pWeight;
//   }
// 
//   @Override
//   protected void fillVIn(XYZPoint pAffineTP, XYZPoint pVarTP, Double4 pVIn) {
//     pVIn.x = pVarTP.x;
//     pVIn.y = pVarTP.y;
//     pVIn.z = pVarTP.z;
//     pVIn.c = pVarTP.color;
//   }
// 
//   @Override
//   public int getPriority() {
//     return 1;
//   }
// }
// 
