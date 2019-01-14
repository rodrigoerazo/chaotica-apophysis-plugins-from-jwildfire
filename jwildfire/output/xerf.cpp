/*
    Apophysis Plugin: xerf

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/XErfFunc.java

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

GOODRAND_STRUCT;
} Variables;

#define APO_VARIABLE_PREFIX "xerf_"
#include "plugin.h"

APO_PLUGIN("xerf");
APO_VARIABLES(

);



int PluginVarPrepare(Variation* vp)
{
    GOODRAND_PREPARE();

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    // "xerf" variation created by zephyrtronium implemented into JWildfire by darkbeam

    double r2 = sqr(sqrt(sqr(FTx) + sqr(FTy) + sqr(FTz))); // sqr sqrt??? whatever
    if (r2 <= SMALL_EPSILON) r2 = SMALL_EPSILON; // no overflow fix by Dark

    FPx += ((fabs(FTx) >= 2.0) ? (FTx / r2) : erf(FTx)) * VVAR;
    FPy += ((fabs(FTy) >= 2.0) ? (FTy / r2) : erf(FTy)) * VVAR;
    FPz += ((fabs(FTz) >= 2.0) ? (FTz / r2) : erf(FTz)) * VVAR;


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
// import org.jwildfire.create.tina.base.XForm;
// import org.jwildfire.create.tina.base.XYZPoint;
// 
// import static org.jwildfire.base.mathlib.MathLib.*;
// 
// 
// public class XErfFunc extends SimpleVariationFunc {
//   private static final long serialVersionUID = 1L;
// 
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     // "xerf" variation created by zephyrtronium implemented into JWildfire by darkbeam
// 
//     double r2 = sqr(sqrt(sqr(pAffineTP.x) + sqr(pAffineTP.y) + sqr(pAffineTP.z))); // sqr sqrt??? whatever
//     if (r2 <= SMALL_EPSILON) r2 = SMALL_EPSILON; // no overflow fix by Dark
// 
//     pVarTP.x += ((fabs(pAffineTP.x) >= 2.0) ? (pAffineTP.x / r2) : erf(pAffineTP.x)) * pAmount;
//     pVarTP.y += ((fabs(pAffineTP.y) >= 2.0) ? (pAffineTP.y / r2) : erf(pAffineTP.y)) * pAmount;
//     pVarTP.z += ((fabs(pAffineTP.z) >= 2.0) ? (pAffineTP.z / r2) : erf(pAffineTP.z)) * pAmount;
//   }
// 
// 
//   @Override
//   public String getName() {
//     return "xerf";
//   }
// 
// }
