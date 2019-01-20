#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: loonie2

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/Loonie2Func.java

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
	int sides;
	double star;
	double circle;
	double _sqrvvar;
	double _sina;
	double _cosa;
	double _sins;
	double _coss;
	double _sinc;
	double _cosc;

    int ___warning;
} Variables;

#define APO_VARIABLE_PREFIX "loonie2_"
#include "plugin.h"

APO_PLUGIN("loonie2");
APO_VARIABLES(
	VAR_INTEGER(sides, 4),
	VAR_REAL(star, 0.0),
	VAR_REAL(circle, 0.0),

);



int PluginVarPrepare(Variation* vp)
{
    VAR(_sqrvvar) = VVAR * VVAR;

    double a = M_2PI / VAR(sides);
    VAR(_sina) = sin(a);
    VAR(_cosa) = cos(a);

    a = -M_PI_2 * VAR(star);
    VAR(_sins) = sin(a);
    VAR(_coss) = cos(a);

    a = M_PI_2 * VAR(circle);
    VAR(_sinc) = sin(a);
    VAR(_cosc) = cos(a);

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    /* loonie2 by dark-beam, http://dark-beam.deviantart.com/art/Loonie2-update-2-Loonie3-457414891 */
    double xrt = FTx, yrt = FTy, swp;
    // r2 = xrt; // normal
    double r2 = xrt * VAR(_coss) + fabs(yrt) * VAR(_sins); // +VAR(star)
    double VAR(circle) = sqrt(sqr(xrt) + sqr(yrt));

    int i;

    for (i = 0; i < VAR(sides) - 1; i++) {
      // rotate around to get the the VAR(sides)!!! :D
      swp = xrt * VAR(_cosa) - yrt * VAR(_sina);
      yrt = xrt * VAR(_sina) + yrt * VAR(_cosa);
      xrt = swp;

      // r2 = MAX(r2, xrt); // normal
      r2 = MAX(r2, xrt * VAR(_coss) + fabs(yrt) * VAR(_sins)); // +VAR(star)
    }
    r2 = r2 * VAR(_cosc) + VAR(circle) * VAR(_sinc); // +VAR(circle)
    if (i > 1) {
      r2 = sqr(r2); // we want it squared, for the pretty effect
    } else {
      r2 = fabs(r2) * r2; // 2-faces effect JUST FOR i=1
    }

    if (r2 > 0 && (r2 < VAR(_sqrvvar))) {
      double r = VVAR * sqrt(fabs(VAR(_sqrvvar) / r2 - 1.0));
      FPx += r * FTx;
      FPy += r * FTy;
    } else if (r2 < 0) {// 2-faces effect JUST FOR i=1
      double r = VVAR / sqrt(fabs(VAR(_sqrvvar) / r2) - 1.0);
      FPx += r * FTx;
      FPy += r * FTy;
    } else {
      FPx += VVAR * FTx;
      FPy += VVAR * FTy;
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
// import org.jwildfire.base.Tools;
// import org.jwildfire.create.tina.base.Layer;
// import org.jwildfire.create.tina.base.XForm;
// import org.jwildfire.create.tina.base.XYZPoint;
// 
// import static org.jwildfire.base.mathlib.MathLib.*;
// 
// public class Loonie2Func extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_SIDES = "sides";
//   private static final String PARAM_STAR = "star";
//   private static final String PARAM_CIRCLE = "circle";
//   private static final String[] paramNames = {PARAM_SIDES, PARAM_STAR, PARAM_CIRCLE};
// 
//   private int sides = 4;
//   private double star = 0.0;
//   private double circle = 0.0;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     /* loonie2 by dark-beam, http://dark-beam.deviantart.com/art/Loonie2-update-2-Loonie3-457414891 */
//     double xrt = pAffineTP.x, yrt = pAffineTP.y, swp;
//     // r2 = xrt; // normal
//     double r2 = xrt * _coss + fabs(yrt) * _sins; // +star
//     double circle = sqrt(sqr(xrt) + sqr(yrt));
// 
//     int i;
// 
//     for (i = 0; i < sides - 1; i++) {
//       // rotate around to get the the sides!!! :D
//       swp = xrt * _cosa - yrt * _sina;
//       yrt = xrt * _sina + yrt * _cosa;
//       xrt = swp;
// 
//       // r2 = MAX(r2, xrt); // normal
//       r2 = Math.max(r2, xrt * _coss + fabs(yrt) * _sins); // +star
//     }
//     r2 = r2 * _cosc + circle * _sinc; // +circle
//     if (i > 1) {
//       r2 = sqr(r2); // we want it squared, for the pretty effect
//     } else {
//       r2 = fabs(r2) * r2; // 2-faces effect JUST FOR i=1
//     }
// 
//     if (r2 > 0 && (r2 < _sqrvvar)) {
//       double r = pAmount * sqrt(fabs(_sqrvvar / r2 - 1.0));
//       pVarTP.x += r * pAffineTP.x;
//       pVarTP.y += r * pAffineTP.y;
//     } else if (r2 < 0) {// 2-faces effect JUST FOR i=1
//       double r = pAmount / sqrt(fabs(_sqrvvar / r2) - 1.0);
//       pVarTP.x += r * pAffineTP.x;
//       pVarTP.y += r * pAffineTP.y;
//     } else {
//       pVarTP.x += pAmount * pAffineTP.x;
//       pVarTP.y += pAmount * pAffineTP.y;
//     }
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
//     return new Object[]{sides, star, circle};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_SIDES.equalsIgnoreCase(pName))
//       sides = limitIntVal(Tools.FTOI(pValue), 1, 50);
//     else if (PARAM_STAR.equalsIgnoreCase(pName))
//       star = limitVal(pValue, -1.0, 1.0);
//     else if (PARAM_CIRCLE.equalsIgnoreCase(pName))
//       circle = limitVal(pValue, -1.0, 1.0);
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "loonie2";
//   }
// 
//   private double _sqrvvar, _sina, _cosa, _sins, _coss, _sinc, _cosc;
// 
//   @Override
//   public void init(FlameTransformationContext pContext, Layer pLayer, XForm pXForm, double pAmount) {
//     _sqrvvar = pAmount * pAmount;
// 
//     double a = M_2PI / sides;
//     _sina = sin(a);
//     _cosa = cos(a);
// 
//     a = -M_PI_2 * star;
//     _sins = sin(a);
//     _coss = cos(a);
// 
//     a = M_PI_2 * circle;
//     _sinc = sin(a);
//     _cosc = cos(a);
//   }
// }
// 
