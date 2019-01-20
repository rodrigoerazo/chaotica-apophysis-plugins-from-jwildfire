#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: foci

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/FociFunc.java

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

#define APO_VARIABLE_PREFIX "foci_"
#include "plugin.h"

APO_PLUGIN("foci");
APO_VARIABLES(

);



int PluginVarPrepare(Variation* vp)
{

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    /* Foci in the Apophysis Plugin Pack */

    double expx = exp(FTx) * 0.5;
    double expnx = 0.25 / expx;
    if (expx <= SMALL_EPSILON || expnx <= SMALL_EPSILON) {
      return TRUE;
    }
    double siny = sin(FTy);
    double cosy = cos(FTy);

    double tmp = (expx + expnx - cosy);
    if (tmp == 0)
      return TRUE;
    tmp = VVAR / tmp;

    FPx += (expx - expnx) * tmp;
    FPy += siny * tmp;
    if (true /* pContext\.isPreserveZCoordinate() */) {
      FPz += VVAR * FTz;
    }


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
// public class FociFunc extends SimpleVariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     /* Foci in the Apophysis Plugin Pack */
// 
//     double expx = exp(pAffineTP.x) * 0.5;
//     double expnx = 0.25 / expx;
//     if (expx <= SMALL_EPSILON || expnx <= SMALL_EPSILON) {
//       return;
//     }
//     double siny = sin(pAffineTP.y);
//     double cosy = cos(pAffineTP.y);
// 
//     double tmp = (expx + expnx - cosy);
//     if (tmp == 0)
//       return;
//     tmp = pAmount / tmp;
// 
//     pVarTP.x += (expx - expnx) * tmp;
//     pVarTP.y += siny * tmp;
//     if (pContext.isPreserveZCoordinate()) {
//       pVarTP.z += pAmount * pAffineTP.z;
//     }
//   }
// 
//   @Override
//   public String getName() {
//     return "foci";
//   }
// 
// }
// 
