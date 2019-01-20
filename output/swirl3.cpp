#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: swirl3

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/Swirl3Func.java

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
	double shift;

    int ___warning;
} Variables;

#define APO_VARIABLE_PREFIX "swirl3_"
#include "plugin.h"

APO_PLUGIN("swirl3");
APO_VARIABLES(
	VAR_REAL(shift, 0.5),

);



int PluginVarPrepare(Variation* vp)
{

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{

    double rad = (sqrt(FTx * FTx + FTy * FTy) + SMALL_EPSILON);
    double ang = atan2(FTx, FTy) + log(rad) * VAR(shift);
    double s = sin(ang);
    double c = cos(ang);

    FPx += VVAR * rad * c;
    FPy += VVAR * rad * s;

    if (true /* pContext\.isPreserveZCoordinate() */) FPz += VVAR * FTz;



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
// public class Swirl3Func extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_SHIFT = "shift";
// 
//   private static final String[] paramNames = {PARAM_SHIFT};
// 
//   private double shift = 0.5;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
// 
//     double rad = pAffineTP.getPrecalcSqrt();
//     double ang = pAffineTP.getPrecalcAtanYX() + log(rad) * shift;
//     double s = sin(ang);
//     double c = cos(ang);
// 
//     pVarTP.x += pAmount * rad * c;
//     pVarTP.y += pAmount * rad * s;
// 
//     if (pContext.isPreserveZCoordinate()) pVarTP.z += pAmount * pAffineTP.z;
// 
//   }
// 
//   @Override
//   public String[] getParameterNames() {
//     return paramNames;
//   }
// 
//   @Override
//   public Object[] getParameterValues() {
//     return new Object[]{shift};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_SHIFT.equalsIgnoreCase(pName))
//       shift = pValue;
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "swirl3";
//   }
// 
// }
// 
