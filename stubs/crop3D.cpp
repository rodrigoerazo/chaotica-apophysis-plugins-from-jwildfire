#define PLUGIN_WARNING "_WARNING_empty_shim_for_jw_workflow"
/*
    Apophysis Plugin: crop3D

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/Crop3DFunc.java

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
	double left; // -1.0
	double top; // -1.0
	double floor; // -1.0
	double right;
	double bottom;
	double ceiling;
	double scatter_area;
	int zero;
	double _xmin;
	double _xmax;
	double _ymin;
	double _ymax;
	double _zmin;
	double _zmax;
	double _w;
	double _h;
	double _l;

} Variables;

#define APO_VARIABLE_PREFIX "crop3D_"
#include "plugin.h"

APO_PLUGIN("crop3D");
APO_VARIABLES(
	VAR_REAL(left, -1.0),
	VAR_REAL(top, -1.0),
	VAR_REAL(floor, -1.0),
	VAR_REAL(right, 1.0),
	VAR_REAL(bottom, 1.0),
	VAR_REAL(ceiling, 1.0),
	VAR_REAL(scatter_area, 0.0),
	VAR_INTEGER(zero, 0)

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
// import org.jwildfire.base.Tools;
// import org.jwildfire.create.tina.base.Layer;
// import org.jwildfire.create.tina.base.XForm;
// import org.jwildfire.create.tina.base.XYZPoint;
// 
// import static org.jwildfire.base.mathlib.MathLib.max;
// import static org.jwildfire.base.mathlib.MathLib.min;
// 
// public class Crop3DFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_LEFT = "left";
//   private static final String PARAM_RIGHT = "right";
//   private static final String PARAM_TOP = "top";
//   private static final String PARAM_CEILING = "ceiling";
//   private static final String PARAM_BOTTOM = "bottom";
//   private static final String PARAM_FLOOR = "floor";
//   private static final String PARAM_SCATTER_AREA = "scatter_area";
//   private static final String PARAM_ZERO = "zero";
// 
//   private static final String[] paramNames = {PARAM_LEFT, PARAM_RIGHT, PARAM_TOP, PARAM_BOTTOM, PARAM_FLOOR, PARAM_CEILING, PARAM_SCATTER_AREA, PARAM_ZERO};
// 
//   private double left = -1.0;
//   private double top = -1.0;
//   private double floor = -1.0;
//   private double right = 1.0;
//   private double bottom = 1.0;
//   private double ceiling = 1.0;
//   private double scatter_area = 0.0;
//   private int zero = 0;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     // 3D version of crop by Xyrus02, http://xyrus02.deviantart.com/art/Crop-Plugin-Updated-169958881
//     double x = pAffineTP.x;
//     double y = pAffineTP.y;
//     double z = pAffineTP.z;
//     if (((x < xmin) || (x > xmax) || (y < ymin) || (y > ymax) || (z < zmin) || (z > zmax)) && (zero != 0)) {
//       pVarTP.x = pVarTP.y = pVarTP.z = 0;
//       pVarTP.doHide = true;
//       return;
//     } else {
//       pVarTP.doHide = false;
//       if (x < xmin)
//         x = xmin + pContext.random() * w;
//       else if (x > xmax)
//         x = xmax - pContext.random() * w;
//       if (y < ymin)
//         y = ymin + pContext.random() * h;
//       else if (y > ymax)
//         y = ymax - pContext.random() * h;
//       if (z < zmin)
//         z = zmin + pContext.random() * l;
//       else if (z > zmax)
//         z = zmax - pContext.random() * l;
//     }
//     pVarTP.x = pAmount * x;
//     pVarTP.y = pAmount * y;
//     pVarTP.z = pAmount * z;
//   }
// 
//   @Override
//   public String[] getParameterNames() {
//     return paramNames;
//   }
// 
//   @Override
//   public Object[] getParameterValues() {
//     return new Object[]{left, right, top, bottom, floor, ceiling, scatter_area, zero};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_LEFT.equalsIgnoreCase(pName))
//       left = pValue;
//     else if (PARAM_RIGHT.equalsIgnoreCase(pName))
//       right = pValue;
//     else if (PARAM_TOP.equalsIgnoreCase(pName))
//       top = pValue;
//     else if (PARAM_BOTTOM.equalsIgnoreCase(pName))
//       bottom = pValue;
//     else if (PARAM_CEILING.equalsIgnoreCase(pName))
//       ceiling = pValue;
//     else if (PARAM_FLOOR.equalsIgnoreCase(pName))
//       floor = pValue;
//     else if (PARAM_SCATTER_AREA.equalsIgnoreCase(pName))
//       scatter_area = limitVal(pValue, -1.0, 1.0);
//     else if (PARAM_ZERO.equalsIgnoreCase(pName))
//       zero = limitIntVal(Tools.FTOI(pValue), 0, 1);
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "crop3D";
//   }
// 
//   private double xmin, xmax, ymin, ymax, zmin, zmax, w, h, l;
// 
//   @Override
//   public void init(FlameTransformationContext pContext, Layer pLayer, XForm pXForm, double pAmount) {
//     xmin = min(left, right);
//     ymin = min(top, bottom);
//     zmin = min(floor, ceiling);
//     xmax = max(left, right);
//     ymax = max(top, bottom);
//     zmax = max(floor, ceiling);
//     w = (xmax - xmin) * 0.5 * scatter_area;
//     h = (ymax - ymin) * 0.5 * scatter_area;
//     l = (zmax - zmin) * 0.5 * scatter_area;
//   }
// 
// }
// 
