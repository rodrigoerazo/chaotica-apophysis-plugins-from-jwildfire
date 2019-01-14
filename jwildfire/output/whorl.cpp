/*
    Apophysis Plugin: whorl

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/WhorlFunc.java

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
	double inside;
	double outside;

GOODRAND_STRUCT;
} Variables;

#define APO_VARIABLE_PREFIX "whorl_"
#include "plugin.h"

APO_PLUGIN("whorl");
APO_VARIABLES(
	VAR_REAL(inside, 0.10),
	VAR_REAL(outside, 0.20),

);



int PluginVarPrepare(Variation* vp)
{
    GOODRAND_PREPARE();

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    /* whorl from apo plugins pack */
    double r = (sqrt(FTx * FTx + FTy * FTy) + SMALL_EPSILON);
    double a;
    if (r < VVAR)
      a = atan2(FTx, FTy) + VAR(inside) / (VVAR - r);
    else
      a = atan2(FTx, FTy) + VAR(outside) / (VVAR - r);

    double sa = sin(a);
    double ca = cos(a);

    FPx += VVAR * r * ca;
    FPy += VVAR * r * sa;
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
// import static org.jwildfire.base.mathlib.MathLib.cos;
// import static org.jwildfire.base.mathlib.MathLib.sin;
// 
// public class WhorlFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_INSIDE = "inside";
//   private static final String PARAM_OUTSIDE = "outside";
// 
//   private static final String[] paramNames = {PARAM_INSIDE, PARAM_OUTSIDE};
// 
//   private double inside = 0.10;
//   private double outside = 0.20;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     /* whorl from apo plugins pack */
//     double r = pAffineTP.getPrecalcSqrt();
//     double a;
//     if (r < pAmount)
//       a = pAffineTP.getPrecalcAtanYX() + inside / (pAmount - r);
//     else
//       a = pAffineTP.getPrecalcAtanYX() + outside / (pAmount - r);
// 
//     double sa = sin(a);
//     double ca = cos(a);
// 
//     pVarTP.x += pAmount * r * ca;
//     pVarTP.y += pAmount * r * sa;
//     if (pContext.isPreserveZCoordinate()) {
//       pVarTP.z += pAmount * pAffineTP.z;
//     }
//   }
// 
//   @Override
//   public String[] getParameterNames() {
//     return paramNames;
//   }
// 
//   @Override
//   public Object[] getParameterValues() {
//     return new Object[]{inside, outside};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_INSIDE.equalsIgnoreCase(pName))
//       inside = pValue;
//     else if (PARAM_OUTSIDE.equalsIgnoreCase(pName))
//       outside = pValue;
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "whorl";
//   }
// 
// }
// 
