#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: circlesplit

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/CirclesplitFunc.java

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
	double cs_radius;
	double cs_split;

    int ___warning;
} Variables;

#define APO_VARIABLE_PREFIX "circlesplit_"
#include "plugin.h"

APO_PLUGIN("circlesplit");
APO_VARIABLES(
	VAR_REAL(cs_radius, 1.0),
	VAR_REAL(cs_split, 0.5),

);



int PluginVarPrepare(Variation* vp)
{

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    // "circlesplit" variation created by Tatyana Zabanova implemented into JWildfire by Brad Stefanov

    double x0 = FTx;
    double y0 = FTy;

    double r = sqrt(sqr(x0) + sqr(y0));

    double x1;
    double y1;

    if (r < VAR(cs_radius) - VAR(cs_split)) {
      x1 = x0;
      y1 = y0;
    } else {
      double a = atan2(y0, x0);
      double len = r + VAR(cs_split);
      x1 = cos(a) * len;
      y1 = sin(a) * len;
    }

    FPx += VVAR * x1;
    FPy += VVAR * y1;
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
// public class CirclesplitFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
//   private static final String PARAM_CS_RADIUS = "cs_radius";
//   private static final String PARAM_CS_SPLIT = "cs_split";
//   private static final String[] paramNames = {PARAM_CS_RADIUS, PARAM_CS_SPLIT};
//   private double cs_radius = 1.0;
//   private double cs_split = 0.5;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     // "circlesplit" variation created by Tatyana Zabanova implemented into JWildfire by Brad Stefanov
// 
//     double x0 = pAffineTP.x;
//     double y0 = pAffineTP.y;
// 
//     double r = sqrt(sqr(x0) + sqr(y0));
// 
//     double x1;
//     double y1;
// 
//     if (r < cs_radius - cs_split) {
//       x1 = x0;
//       y1 = y0;
//     } else {
//       double a = atan2(y0, x0);
//       double len = r + cs_split;
//       x1 = cos(a) * len;
//       y1 = sin(a) * len;
//     }
// 
//     pVarTP.x += pAmount * x1;
//     pVarTP.y += pAmount * y1;
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
//     return new Object[]{cs_radius, cs_split};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_CS_RADIUS.equalsIgnoreCase(pName))
//       cs_radius = pValue;
//     else if (PARAM_CS_SPLIT.equalsIgnoreCase(pName))
//       cs_split = pValue;
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "circlesplit";
//   }
// }
