/*
    Apophysis Plugin: shift

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/ShiftFunc.java

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
	double shift_x;
	double shift_y;
	double angle;

GOODRAND_STRUCT;
} Variables;

#define APO_VARIABLE_PREFIX "shift_"
#include "plugin.h"

APO_PLUGIN("shift");
APO_VARIABLES(
	VAR_REAL(shift_x, 0.0),
	VAR_REAL(shift_y, 0.0),
	VAR_REAL(angle, 0.0),

);



int PluginVarPrepare(Variation* vp)
{
    GOODRAND_PREPARE();

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    // "shift" variation created by Tatyana Zabanova implemented into JWildfire by Brad Stefanov

    double ang = VAR(angle) / 180 * M_PI;

    double sn = sin(ang);
    double cs = cos(ang);


    FPx += VVAR * (FTx + cs * VAR(shift_x) - sn * VAR(shift_y));
    FPy += VVAR * (FTy - cs * VAR(shift_y) - sn * VAR(shift_x));
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
// public class ShiftFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_SHIFT_X = "shift_x";
//   private static final String PARAM_SHIFT_Y = "shift_y";
//   private static final String PARAM_ANGLE = "angle";
//   private static final String[] paramNames = {PARAM_SHIFT_X, PARAM_SHIFT_Y, PARAM_ANGLE};
//   private double shift_x = 0.0;
//   private double shift_y = 0.0;
//   private double angle = 0.0;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     // "shift" variation created by Tatyana Zabanova implemented into JWildfire by Brad Stefanov
// 
//     double ang = angle / 180 * M_PI;
// 
//     double sn = sin(ang);
//     double cs = cos(ang);
// 
// 
//     pVarTP.x += pAmount * (pAffineTP.x + cs * shift_x - sn * shift_y);
//     pVarTP.y += pAmount * (pAffineTP.y - cs * shift_y - sn * shift_x);
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
//     return new Object[]{shift_x, shift_y, angle};
//   }
// 
//   @Override
//   public String[] getParameterAlternativeNames() {
//     return new String[]{"shift_x", "shift_y", "shift_angle"};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_SHIFT_X.equalsIgnoreCase(pName))
//       shift_x = pValue;
//     else if (PARAM_SHIFT_Y.equalsIgnoreCase(pName))
//       shift_y = pValue;
//     else if (PARAM_ANGLE.equalsIgnoreCase(pName))
//       angle = pValue;
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "shift";
//   }
// }
// 
