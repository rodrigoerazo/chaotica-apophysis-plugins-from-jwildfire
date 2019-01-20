#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: gridout

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/GridoutFunc.java

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

#define APO_VARIABLE_PREFIX "gridout_"
#include "plugin.h"

APO_PLUGIN("gridout");
APO_VARIABLES(

);



int PluginVarPrepare(Variation* vp)
{

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    // authors Michael Faber, Joel Faber 2007-2008.0 Implemented by DarkBeam 2017
    double x = rint(FTx);
    double y = rint(FTy);

    if (y <= 0.0) {
      if (x > 0.0) {
        if (-y >= x) {
          FPx += VVAR * (FTx + 1.0);
          FPy += VVAR * FTy;
        } else {
          FPx += VVAR * FTx;
          FPy += VVAR * (FTy + 1.0);
        }
      } else {
        if (y <= x) {
          FPx += VVAR * (FTx + 1.0);
          FPy += VVAR * FTy;
        } else {
          FPx += VVAR * FTx;
          FPy += VVAR * (FTy - 1.0);
        }
      }
    } else {
      if (x > 0.0) {
        if (y >= x) {
          FPx += VVAR * (FTx - 1.0);
          FPy += VVAR * FTy;
        } else {
          FPx += VVAR * FTx;
          FPy += VVAR * (FTy + 1.0);
        }
      } else {
        if (y > -x) {
          FPx += VVAR * (FTx - 1.0);
          FPy += VVAR * FTy;
        } else {
          FPx += VVAR * FTx;
          FPy += VVAR * (FTy - 1.0);
        }
      }
    }
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
//   This is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser 
//   General Public License as published by the Free Software Foundation; either version 2.1 of the 
//   License, or (at your option) any later version.
//  
//   This software is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without 
//   even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
//   Lesser General Public License for more details.
//   You should have received a copy of the GNU Lesser General Public License along with this software; 
//   if not, write to the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
//   02110-1301 USA, or see the FSF site: http://www.fsf.org.
// */
// package org.jwildfire.create.tina.variation;
// 
// import org.jwildfire.create.tina.base.XForm;
// import org.jwildfire.create.tina.base.XYZPoint;
// 
// import static org.jwildfire.base.mathlib.MathLib.rint;
// 
// public class GridoutFunc extends SimpleVariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     // authors Michael Faber, Joel Faber 2007-2008. Implemented by DarkBeam 2017
//     double x = rint(pAffineTP.x);
//     double y = rint(pAffineTP.y);
// 
//     if (y <= 0.0) {
//       if (x > 0.0) {
//         if (-y >= x) {
//           pVarTP.x += pAmount * (pAffineTP.x + 1.0);
//           pVarTP.y += pAmount * pAffineTP.y;
//         } else {
//           pVarTP.x += pAmount * pAffineTP.x;
//           pVarTP.y += pAmount * (pAffineTP.y + 1.0);
//         }
//       } else {
//         if (y <= x) {
//           pVarTP.x += pAmount * (pAffineTP.x + 1.0);
//           pVarTP.y += pAmount * pAffineTP.y;
//         } else {
//           pVarTP.x += pAmount * pAffineTP.x;
//           pVarTP.y += pAmount * (pAffineTP.y - 1.0);
//         }
//       }
//     } else {
//       if (x > 0.0) {
//         if (y >= x) {
//           pVarTP.x += pAmount * (pAffineTP.x - 1.0);
//           pVarTP.y += pAmount * pAffineTP.y;
//         } else {
//           pVarTP.x += pAmount * pAffineTP.x;
//           pVarTP.y += pAmount * (pAffineTP.y + 1.0);
//         }
//       } else {
//         if (y > -x) {
//           pVarTP.x += pAmount * (pAffineTP.x - 1.0);
//           pVarTP.y += pAmount * pAffineTP.y;
//         } else {
//           pVarTP.x += pAmount * pAffineTP.x;
//           pVarTP.y += pAmount * (pAffineTP.y - 1.0);
//         }
//       }
//     }
//     if (pContext.isPreserveZCoordinate()) {
//       pVarTP.z += pAmount * pAffineTP.z;
//     }
//   }
// 
//   @Override
//   public String getName() {
//     return "gridout";
//   }
// 
// }
// 
