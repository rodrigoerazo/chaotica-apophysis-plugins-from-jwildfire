/*
    Apophysis Plugin: arctanh

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/ArctanhFunc.java

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

    int ___warning;
} Variables;

#define APO_VARIABLE_PREFIX "arctanh_"
#include "plugin.h"

APO_PLUGIN("arctanh");
APO_VARIABLES(

    { "WARNING_this_plugin_does_nothing", INTEGER, OFFSET(___warning), 0, 1, 0 },
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
//   This is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser 
//   General Public License as published by the Free Software Foundation; either version 2.1 of the 
//   License, or (at your option) any later version.
//  
//   This software is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without 
//   even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
//   Lesser General Public License for more details.
//   You should have received a copy of the GNU Lesser General Public License along with this software; 
//   if not, write to the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
//   02110-1301 USA, or see the FSF site: http://www.fsf.org.
// */
// package org.jwildfire.create.tina.variation;
// 
// import org.jwildfire.base.mathlib.Complex;
// import org.jwildfire.create.tina.base.XForm;
// import org.jwildfire.create.tina.base.XYZPoint;
// 
// import static org.jwildfire.base.mathlib.MathLib.M_2_PI;
// 
// 
// public class ArctanhFunc extends SimpleVariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     // author Tatyana Zabanova 2017. Implemented by DarkBeam 2018
// 
//     Complex z = new Complex(pAffineTP.x, pAffineTP.y);
//     Complex z2 = new Complex(z);
//     z2.Scale(-1.0);
//     z2.Inc(); // -z+1
//     Complex z3 = new Complex(z);
//     z3.Inc(); // z+1
//     z3.Div(z2);
//     z3.Log();
//     z3.Scale(pAmount * M_2_PI);
//     pVarTP.x += z3.re;
//     pVarTP.y += z3.im;
//     if (pContext.isPreserveZCoordinate()) {
//       pVarTP.z += pAmount * pAffineTP.z;
//     }
//   }
// 
//   @Override
//   public String getName() {
//     return "arctanh";
//   }
// 
// }
// 
