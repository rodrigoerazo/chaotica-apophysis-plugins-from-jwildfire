#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: farblur

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/FarBlurFunc.java

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
	double z;
	double x_origin;
	double y_origin;
	double z_origin;
	double _r[4];
	int _n;

    int ___warning;
} Variables;

#define APO_VARIABLE_PREFIX "farblur_"
#include "plugin.h"

APO_PLUGIN("farblur");
APO_VARIABLES(
	VAR_REAL(x, 1.0),
	VAR_REAL(y, 1.0),
	VAR_REAL(z, 1.0),
	VAR_REAL(x_origin, 0.0),
	VAR_REAL(y_origin, 0.0),
	VAR_REAL(z_origin, 0.0),

);



int PluginVarPrepare(Variation* vp)
{
    VAR(_n) = 0;
    VAR(_r)[0] = GOODRAND_01();
    VAR(_r)[1] = GOODRAND_01();
    VAR(_r)[2] = GOODRAND_01();
    VAR(_r)[3] = GOODRAND_01();

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    /* farblur by zephyrtronium, http://zephyrtronium.deviantart.com/art/Farblur-Apophysis-Plugin-170718419?q=gallery%3Afractal-resources%2F24660058&qo=10 */
    double r = VVAR * (sqr(FPx - VAR(x_origin)) +
            sqr(FPy - VAR(y_origin)) +
            sqr(FPz - VAR(z_origin))) *
            (VAR(_r)[0] + VAR(_r)[1] + VAR(_r)[2] + VAR(_r)[3] - 2.0);
    VAR(_r)[VAR(_n)] = GOODRAND_01();
    VAR(_n) = (VAR(_n) + 1) & 3;
    double u = GOODRAND_01() * M_2PI;
    double su = sin(u);
    double cu = cos(u);
    double v = GOODRAND_01() * M_2PI;
    double sv = sin(v);
    double cv = cos(v);

    FPx += VAR(x) * r * sv * cu;
    FPy += VAR(y) * r * sv * su;
    FPz += VAR(z) * r * cv;


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
// import org.jwildfire.create.tina.base.Layer;
// import org.jwildfire.create.tina.base.XForm;
// import org.jwildfire.create.tina.base.XYZPoint;
// 
// import static org.jwildfire.base.mathlib.MathLib.*;
// 
// public class FarBlurFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_X = "x";
//   private static final String PARAM_Y = "y";
//   private static final String PARAM_Z = "z";
//   private static final String PARAM_X_ORIGIN = "x_origin";
//   private static final String PARAM_Y_ORIGIN = "y_origin";
//   private static final String PARAM_Z_ORIGIN = "z_origin";
// 
//   private static final String[] paramNames = {PARAM_X, PARAM_Y, PARAM_Z, PARAM_X_ORIGIN, PARAM_Y_ORIGIN, PARAM_Z_ORIGIN};
// 
//   private double x = 1.0;
//   private double y = 1.0;
//   private double z = 1.0;
//   private double x_origin = 0.0;
//   private double y_origin = 0.0;
//   private double z_origin = 0.0;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     /* farblur by zephyrtronium, http://zephyrtronium.deviantart.com/art/Farblur-Apophysis-Plugin-170718419?q=gallery%3Afractal-resources%2F24660058&qo=10 */
//     double r = pAmount * (sqr(pVarTP.x - x_origin) +
//             sqr(pVarTP.y - y_origin) +
//             sqr(pVarTP.z - z_origin)) *
//             (this._r[0] + this._r[1] + this._r[2] + this._r[3] - 2.0);
//     this._r[_n] = pContext.random();
//     _n = (_n + 1) & 3;
//     double u = pContext.random() * M_2PI;
//     double su = sin(u);
//     double cu = cos(u);
//     double v = pContext.random() * M_2PI;
//     double sv = sin(v);
//     double cv = cos(v);
// 
//     pVarTP.x += x * r * sv * cu;
//     pVarTP.y += y * r * sv * su;
//     pVarTP.z += z * r * cv;
//   }
// 
//   @Override
//   public String[] getParameterNames() {
//     return paramNames;
//   }
// 
//   @Override
//   public Object[] getParameterValues() {
//     return new Object[]{x, y, z, x_origin, y_origin, z_origin};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_X.equalsIgnoreCase(pName))
//       x = pValue;
//     else if (PARAM_Y.equalsIgnoreCase(pName))
//       y = pValue;
//     else if (PARAM_Z.equalsIgnoreCase(pName))
//       z = pValue;
//     else if (PARAM_X_ORIGIN.equalsIgnoreCase(pName))
//       x_origin = pValue;
//     else if (PARAM_Y_ORIGIN.equalsIgnoreCase(pName))
//       y_origin = pValue;
//     else if (PARAM_Z_ORIGIN.equalsIgnoreCase(pName))
//       z_origin = pValue;
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "farblur";
//   }
// 
//   private double _r[] = new double[4];
//   private int _n;
// 
//   @Override
//   public void init(FlameTransformationContext pContext, Layer pLayer, XForm pXForm, double pAmount) {
//     _n = 0;
//     _r[0] = pContext.random();
//     _r[1] = pContext.random();
//     _r[2] = pContext.random();
//     _r[3] = pContext.random();
//   }
// 
//   @Override
//   public int getPriority() {
//     return 1;
//   }
// 
// }
// 
