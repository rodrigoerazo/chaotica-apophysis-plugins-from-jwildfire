#define PLUGIN_WARNING "_WARNING_empty_shim_for_jw_workflow"
/*
    Apophysis Plugin: pie

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/PieFunc.java

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
	double slices;
	double rotation;
	double thickness;

} Variables;

#define APO_VARIABLE_PREFIX "pie_"
#include "plugin.h"

APO_PLUGIN("pie");
APO_VARIABLES(
	VAR_REAL(slices, 6.0),
	VAR_REAL(rotation, 0.0),
	VAR_REAL(thickness, 0.5)

);


int PluginVarPrepare(Variation* vp)
{
    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
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
// public class PieFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_SLICES = "slices";
//   private static final String PARAM_ROTATION = "rotation";
//   private static final String PARAM_THICKNESS = "thickness";
//   private static final String[] paramNames = {PARAM_SLICES, PARAM_ROTATION, PARAM_THICKNESS};
// 
//   private double slices = 6.0;
//   private double rotation = 0.0;
//   private double thickness = 0.5;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     int sl = (int) (pContext.random() * slices + 0.5);
//     double a = rotation + 2.0 * M_PI * (sl + pContext.random() * thickness) / slices;
//     double r = pAmount * pContext.random();
//     double sina = sin(a);
//     double cosa = cos(a);
//     pVarTP.x += r * cosa;
//     pVarTP.y += r * sina;
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
//     return new Object[]{slices, rotation, thickness};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_SLICES.equalsIgnoreCase(pName))
//       slices = pValue;
//     else if (PARAM_ROTATION.equalsIgnoreCase(pName))
//       rotation = pValue;
//     else if (PARAM_THICKNESS.equalsIgnoreCase(pName))
//       thickness = pValue;
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "pie";
//   }
// 
// }
// 
