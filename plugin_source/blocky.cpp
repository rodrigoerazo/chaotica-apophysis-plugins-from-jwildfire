/*
    Apophysis Plugin: blocky

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/BlockYFunc.java

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
	double x;
	double y;
	double mp;
	double _v;

GOODRAND_STRUCT;
} Variables;

#define APO_VARIABLE_PREFIX "blocky_"
#include "plugin.h"

APO_PLUGIN("blocky");
APO_VARIABLES(
	VAR_REAL(x, 1.0),
	VAR_REAL(y, 1.0),
	VAR_REAL(mp, 4.0),

);


double sqrt_safe (Variation* vp, double x) {

    if (VAR(x) < 0.0)
      return 0.0;
    return sqrt(VAR(x));
}


int PluginVarPrepare(Variation* vp)
{
    GOODRAND_PREPARE();
    VAR(_v) = VVAR / M_PI_2;

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    /* blocky from FracFx, http://fracfx.deviantart.com/art/FracFx-Plugin-Pack-171806681 */
    double T, r;
    T = ((cos(FTx) + cos(FTy)) / VAR(mp) + 1.0);
    r = VVAR / T;
    double tmp = sqr(FTy) + sqr(FTx) + 1.0;
    double x2 = 2.0 * FTx;
    double y2 = 2.0 * FTy;
    double xmax = 0.5 * (sqrt(tmp + x2) + sqrt(tmp - x2));
    double ymax = 0.5 * (sqrt(tmp + y2) + sqrt(tmp - y2));
    double a = FTx / xmax;
    double b = sqrt_safe(vp, 1.0 - sqr(a));
    FPx += VAR(_v) * atan2(a, b) * r * VAR(x);

    a = FTy / ymax;
    b = sqrt_safe(vp, 1.0 - sqr(a));
    FPy += VAR(_v) * atan2(a, b) * r * VAR(y);
    if (true /* pContext\.isPreserveZCoordinate() */) {
      FPz += VVAR * FTz;
    }


    return TRUE;
}





// original java file embedded here:
//
// /*
//   JWildfire - an image and animation processor written in Java 
//   Copyright (C) 1995-2013 Andreas Maschke
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
// import org.jwildfire.create.tina.base.Layer;
// import org.jwildfire.create.tina.base.XForm;
// import org.jwildfire.create.tina.base.XYZPoint;
// 
// import static org.jwildfire.base.mathlib.MathLib.*;
// 
// public class BlockYFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_X = "x";
//   private static final String PARAM_Y = "y";
//   private static final String PARAM_MP = "mp";
//   private static final String[] paramNames = {PARAM_X, PARAM_Y, PARAM_MP};
// 
//   private double x = 1.0;
//   private double y = 1.0;
//   private double mp = 4.0;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     /* blocky from FracFx, http://fracfx.deviantart.com/art/FracFx-Plugin-Pack-171806681 */
//     double T, r;
//     T = ((cos(pAffineTP.x) + cos(pAffineTP.y)) / mp + 1.0);
//     r = pAmount / T;
//     double tmp = sqr(pAffineTP.y) + sqr(pAffineTP.x) + 1.0;
//     double x2 = 2.0 * pAffineTP.x;
//     double y2 = 2.0 * pAffineTP.y;
//     double xmax = 0.5 * (sqrt(tmp + x2) + sqrt(tmp - x2));
//     double ymax = 0.5 * (sqrt(tmp + y2) + sqrt(tmp - y2));
//     double a = pAffineTP.x / xmax;
//     double b = sqrt_safe(1.0 - sqr(a));
//     pVarTP.x += this.v * atan2(a, b) * r * this.x;
// 
//     a = pAffineTP.y / ymax;
//     b = sqrt_safe(1.0 - sqr(a));
//     pVarTP.y += this.v * atan2(a, b) * r * this.y;
//     if (pContext.isPreserveZCoordinate()) {
//       pVarTP.z += pAmount * pAffineTP.z;
//     }
//   }
// 
//   private double sqrt_safe(double x) {
//     if (x < 0.0)
//       return 0.0;
//     return sqrt(x);
//   }
// 
//   @Override
//   public String[] getParameterNames() {
//     return paramNames;
//   }
// 
//   @Override
//   public Object[] getParameterValues() {
//     return new Object[]{x, y, mp};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_X.equalsIgnoreCase(pName))
//       x = pValue;
//     else if (PARAM_Y.equalsIgnoreCase(pName))
//       y = pValue;
//     else if (PARAM_MP.equalsIgnoreCase(pName))
//       mp = pValue;
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "blocky";
//   }
// 
//   private double v;
// 
//   @Override
//   public void init(FlameTransformationContext pContext, Layer pLayer, XForm pXForm, double pAmount) {
//     v = pAmount / M_PI_2;
//   }
// 
// }
// 
