#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: eCollide

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/ECollideFunc.java

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
	int num;
	double a;
	double _eCa;
	double _eCn_pi;
	double _eCa_eCn;
	double _pi_eCn;

} Variables;

#define APO_VARIABLE_PREFIX "eCollide_"
#include "plugin.h"

APO_PLUGIN("eCollide");
APO_VARIABLES(
	VAR_INTEGER(num, 1),
	VAR_REAL(a, 0.0)

);


double sqrt_safe (Variation* vp, double x) {

    if (x <= 0.0)
      return 0.0;
    return sqrt(x);
}


int PluginVarPrepare(Variation* vp)
{
    VAR(_eCn_pi) = (double) VAR(num) * M_1_PI;
    VAR(_pi_eCn) = M_PI / (double) VAR(num);
    VAR(_eCa) = M_PI * VAR(a);
    VAR(_eCa_eCn) = VAR(_eCa) / (double) VAR(num);

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    // eCollide by Michael Faber, http://michaelfaber.deviantart.com/art/eSeries-306044892
    double tmp = FTy * FTy + FTx * FTx + 1.0;
    double tmp2 = 2.0 * FTx;
    double xmax = (sqrt_safe(vp, tmp + tmp2) + sqrt_safe(vp, tmp - tmp2)) * 0.5;
    double sinnu, cosnu;
    int alt;
    if (xmax < 1.0)
      xmax = 1.0;

    double t = FTx / xmax;
    if (t > 1.0)
      t = 1.0;
    else if (t < -1.0)
      t = -1.0;
    double nu = acos(t); // -Pi < nu < Pi

    alt = (int) (nu * VAR(_eCn_pi));
    if (alt % 2 == 0)
      nu = alt * VAR(_pi_eCn) + fmod(nu + VAR(_eCa_eCn), VAR(_pi_eCn));
    else
      nu = alt * VAR(_pi_eCn) + fmod(nu - VAR(_eCa_eCn), VAR(_pi_eCn));
    if (FTy <= 0.0)
      nu *= -1.0;
    sinnu = sin(nu);
    cosnu = cos(nu);
    FPx += VVAR * xmax * cosnu;
    FPy += VVAR * sqrt(xmax - 1.0) * sqrt(xmax + 1.0) * sinnu;
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
// public class ECollideFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_NUM = "num";
//   private static final String PARAM_A = "a";
// 
//   private static final String[] paramNames = {PARAM_NUM, PARAM_A};
// 
//   private int num = 1;
//   private double a = 0.0;
// 
//   //Taking the square root of numbers close to zero is dangerous.  If x is negative
//   //due to floating point errors we get NaN results.
//   private double sqrt_safe(double x) {
//     if (x <= 0.0)
//       return 0.0;
//     return sqrt(x);
//   }
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     // eCollide by Michael Faber, http://michaelfaber.deviantart.com/art/eSeries-306044892
//     double tmp = pAffineTP.y * pAffineTP.y + pAffineTP.x * pAffineTP.x + 1.0;
//     double tmp2 = 2.0 * pAffineTP.x;
//     double xmax = (sqrt_safe(tmp + tmp2) + sqrt_safe(tmp - tmp2)) * 0.5;
//     double sinnu, cosnu;
//     int alt;
//     if (xmax < 1.0)
//       xmax = 1.0;
// 
//     double t = pAffineTP.x / xmax;
//     if (t > 1.0)
//       t = 1.0;
//     else if (t < -1.0)
//       t = -1.0;
//     double nu = acos(t); // -Pi < nu < Pi
// 
//     alt = (int) (nu * _eCn_pi);
//     if (alt % 2 == 0)
//       nu = alt * _pi_eCn + fmod(nu + _eCa_eCn, _pi_eCn);
//     else
//       nu = alt * _pi_eCn + fmod(nu - _eCa_eCn, _pi_eCn);
//     if (pAffineTP.y <= 0.0)
//       nu *= -1.0;
//     sinnu = sin(nu);
//     cosnu = cos(nu);
//     pVarTP.x += pAmount * xmax * cosnu;
//     pVarTP.y += pAmount * sqrt(xmax - 1.0) * sqrt(xmax + 1.0) * sinnu;
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
//     return new Object[]{num, a};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_NUM.equalsIgnoreCase(pName))
//       num = limitIntVal(Tools.FTOI(pValue), 1, Integer.MAX_VALUE);
//     else if (PARAM_A.equalsIgnoreCase(pName))
//       a = limitVal(pValue, 0.0, 1.0);
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "eCollide";
//   }
// 
//   private double _eCa, _eCn_pi, _eCa_eCn, _pi_eCn;
// 
//   @Override
//   public void init(FlameTransformationContext pContext, Layer pLayer, XForm pXForm, double pAmount) {
//     _eCn_pi = (double) num * M_1_PI;
//     _pi_eCn = M_PI / (double) num;
//     _eCa = M_PI * a;
//     _eCa_eCn = _eCa / (double) num;
//   }
// 
// }
// 
