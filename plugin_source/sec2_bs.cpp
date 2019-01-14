/*
    Apophysis Plugin: sec2_bs

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/Sec2_BSFunc.java

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
	double x1;
	double x2;
	double y1;
	double y2;

GOODRAND_STRUCT;
} Variables;

#define APO_VARIABLE_PREFIX "sec2_bs_"
#include "plugin.h"

APO_PLUGIN("sec2_bs");
APO_VARIABLES(
	VAR_REAL(x1, 1.0),
	VAR_REAL(x2, 1.0),
	VAR_REAL(y1, 1.0),
	VAR_REAL(y2, 1.0),

);



int PluginVarPrepare(Variation* vp)
{
    GOODRAND_PREPARE();

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    /* complex vars by cothe */
    /* exp log sin cos tan sec csc cot sinh cosh tanh sech csch coth */
    /* Variables added by Brad Stefanov */
    //Secant SEC
    double secsin = sin(FTx * VAR(x1));
    double seccos = cos(FTx * VAR(x2));
    double secsinh = sinh(FTy * VAR(y1));
    double seccosh = cosh(FTy * VAR(y2));
    double d = (cos(2.0 * FTx) + cosh(2.0 * FTy));
    if (d == 0) {
      return TRUE;
    }
    double secden = 2.0 / d;
    FPx += VVAR * secden * seccos * seccosh;
    FPy += VVAR * secden * secsin * secsinh;
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
// public class Sec2_BSFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_X1 = "x1";
//   private static final String PARAM_X2 = "x2";
//   private static final String PARAM_Y1 = "y1";
//   private static final String PARAM_Y2 = "y2";
//   private static final String[] paramNames = {PARAM_X1, PARAM_X2, PARAM_Y1, PARAM_Y2};
//   private double x1 = 1.0;
//   private double x2 = 1.0;
//   private double y1 = 1.0;
//   private double y2 = 1.0;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     /* complex vars by cothe */
//     /* exp log sin cos tan sec csc cot sinh cosh tanh sech csch coth */
//     /* Variables added by Brad Stefanov */
//     //Secant SEC
//     double secsin = sin(pAffineTP.x * x1);
//     double seccos = cos(pAffineTP.x * x2);
//     double secsinh = sinh(pAffineTP.y * y1);
//     double seccosh = cosh(pAffineTP.y * y2);
//     double d = (cos(2.0 * pAffineTP.x) + cosh(2.0 * pAffineTP.y));
//     if (d == 0) {
//       return;
//     }
//     double secden = 2.0 / d;
//     pVarTP.x += pAmount * secden * seccos * seccosh;
//     pVarTP.y += pAmount * secden * secsin * secsinh;
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
//     return new Object[]{x1, x2, y1, y2};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_X1.equalsIgnoreCase(pName))
//       x1 = pValue;
//     else if (PARAM_X2.equalsIgnoreCase(pName))
//       x2 = pValue;
//     else if (PARAM_Y1.equalsIgnoreCase(pName))
//       y1 = pValue;
//     else if (PARAM_Y2.equalsIgnoreCase(pName))
//       y2 = pValue;
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
// 
//   @Override
//   public String getName() {
//     return "sec2_bs";
//   }
// 
// }
// 
