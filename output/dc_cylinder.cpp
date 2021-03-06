#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: dc_cylinder

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/DCCylinderFunc.java

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
	double offset;
	double angle;
	double scale;
	double x;
	double y;
	double blur;
	int _n;
	double _r[4];
	double _ldcs;
	double _ldca;

} Variables;

#define APO_VARIABLE_PREFIX "dc_cylinder_"
#include "plugin.h"

APO_PLUGIN("dc_cylinder");
APO_VARIABLES(
	VAR_REAL(offset, 0.0),
	VAR_REAL(angle, 0.0),
	VAR_REAL(scale, 0.5),
	VAR_REAL(x, 0.125),
	VAR_REAL(y, 0.125),
	VAR_REAL(blur, 1.0)

);



int PluginVarPrepare(Variation* vp)
{
    VAR(_n) = 0;
    VAR(_r)[0] = GOODRAND_01();
    VAR(_r)[1] = GOODRAND_01();
    VAR(_r)[2] = GOODRAND_01();
    VAR(_r)[3] = GOODRAND_01();
    VAR(_ldcs) = 1.0 / (VAR(scale) == 0 ? 10e-6 : VAR(scale));
    VAR(_ldca) = VAR(offset) * M_PI;

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    /* dc_cylinder by FracFx, http://fracfx.deviantart.com/art/DC-Cylinder-Plugin-for-Apo-7x-260748952 */

    double a = GOODRAND_01() * M_2PI;
    double sr = sin(a);
    double cr = cos(a);
    double rr = VAR(blur) * (VAR(_r)[0] + VAR(_r)[1] + VAR(_r)[2] + VAR(_r)[3] - 2.0);
    VAR(_r)[VAR(_n)] = GOODRAND_01();
    VAR(_n) = VAR(_n) + 1 & 3;


    FPx += VVAR * sin(FTx + rr * sr) * VAR(x);
    FPy += rr + FTy * VAR(y);
    FPz += VVAR * cos(FTx + rr * cr);

    TC = fmod(fabs(0.5 * (VAR(_ldcs) * ((cos(VAR(angle)) * FPx + sin(VAR(angle)) * FPy + VAR(offset))) + 1.0)), 1.0);



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
// public class DCCylinderFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_OFFSET = "offset";
//   private static final String PARAM_ANGLE = "angle";
//   private static final String PARAM_SCALE = "scale";
//   private static final String PARAM_X = "x";
//   private static final String PARAM_Y = "y";
//   private static final String PARAM_BLUR = "blur";
// 
//   private static final String[] paramNames = {PARAM_OFFSET, PARAM_ANGLE, PARAM_SCALE, PARAM_X, PARAM_Y, PARAM_BLUR};
// 
//   private double offset = 0.0;
//   private double angle = 0.0;
//   private double scale = 0.5;
//   private double x = 0.125;
//   private double y = 0.125;
//   private double blur = 1.0;
//   private int n = 0;
//   private double[] r = {0.0, 0.0, 0.0, 0.0};
//   private double ldcs, ldca;
// 
//   @Override
//   public void init(FlameTransformationContext pContext, Layer pLayer, XForm pXForm, double pAmount) {
//     n = 0;
//     r[0] = pContext.random();
//     r[1] = pContext.random();
//     r[2] = pContext.random();
//     r[3] = pContext.random();
//     ldcs = 1.0 / (scale == 0 ? 10e-6 : scale);
//     ldca = offset * M_PI;
//   }
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     /* dc_cylinder by FracFx, http://fracfx.deviantart.com/art/DC-Cylinder-Plugin-for-Apo-7x-260748952 */
// 
//     double a = pContext.random() * M_2PI;
//     double sr = sin(a);
//     double cr = cos(a);
//     double rr = blur * (r[0] + r[1] + r[2] + r[3] - 2.0);
//     r[n] = pContext.random();
//     n = n + 1 & 3;
// 
// 
//     pVarTP.x += pAmount * sin(pAffineTP.x + rr * sr) * x;
//     pVarTP.y += rr + pAffineTP.y * y;
//     pVarTP.z += pAmount * cos(pAffineTP.x + rr * cr);
// 
//     pVarTP.color = fmod(fabs(0.5 * (ldcs * ((cos(angle) * pVarTP.x + sin(angle) * pVarTP.y + offset)) + 1.0)), 1.0);
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
//     return new Object[]{offset, angle, scale, x, y, blur};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_OFFSET.equalsIgnoreCase(pName))
//       offset = pValue;
//     else if (PARAM_ANGLE.equalsIgnoreCase(pName))
//       angle = pValue;
//     else if (PARAM_SCALE.equalsIgnoreCase(pName))
//       scale = pValue;
//     else if (PARAM_X.equalsIgnoreCase(pName))
//       x = pValue;
//     else if (PARAM_Y.equalsIgnoreCase(pName))
//       y = pValue;
//     else if (PARAM_BLUR.equalsIgnoreCase(pName))
//       blur = pValue;
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String[] getParameterAlternativeNames() {
//     return new String[]{"dc_cyl_offset", "dc_cyl_angle", "dc_cyl_scale", "cyl_x", "cyl_y", "cyl_blur"};
//   }
// 
//   @Override
//   public String getName() {
//     return "dc_cylinder";
//   }
// 
// }
// 
