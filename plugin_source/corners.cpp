/*
    Apophysis Plugin: corners

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/CornersFunc.java

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
	double _multx = 1.0;
	double _multy = 1.0;
	double _xpower = 0.75;
	double _ypower = 0.75;
	double _xypower;
	double _logmode;
	double _log_base = 2.71828;
	double _ex;
	double _ey;

GOODRAND_STRUCT;
} Variables;

#define APO_VARIABLE_PREFIX "corners_"
#include "plugin.h"

APO_PLUGIN("corners");
APO_VARIABLES(
	VAR_REAL(x, 1.0),
	VAR_REAL(y, 1.0),

);



int PluginVarPrepare(Variation* vp)
{
    GOODRAND_PREPARE();
   VAR(_multx) = 1.0;
   VAR(_multy) = 1.0;
   VAR(_xpower) = 0.75;
   VAR(_ypower) = 0.75;
   VAR(_log_base) = 2.71828;

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    // corners by Whittaker Courtney 8-14-2018

    double xs = FTx * FTx;
    double ys = FTy * FTy;

    //log mode
    if (VAR(_logmode) == 0) {
      VAR(_ex) = pow(xs, VAR(_xpower) + VAR(_xypower)) * VAR(_multx);
      VAR(_ey) = pow(ys, VAR(_ypower) + VAR(_xypower)) * VAR(_multy);
    } else {
      VAR(_ex) = pow(log((xs * VAR(_multx)) + 3) / log(VAR(_log_base)), VAR(_xpower) + 2.25 + VAR(_xypower)) - 1.33;
      VAR(_ey) = pow(log((ys * VAR(_multy)) + 3) / log(VAR(_log_base)), VAR(_ypower) + 2.25 + VAR(_xypower)) - 1.33;
    }


    if (FTx > 0) {
      FPx += VVAR * VAR(_ex) + VAR(x);
    } else {
      FPx += VVAR * -VAR(_ex) - VAR(x);
    }

    if (FTy > 0) {
      FPy += VVAR * VAR(_ey) + VAR(y);
    } else {
      FPy += VVAR * -VAR(_ey) - VAR(y);
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
// import org.jwildfire.create.tina.base.XForm;
// import org.jwildfire.create.tina.base.XYZPoint;
// 
// import static org.jwildfire.base.mathlib.MathLib.log;
// import static org.jwildfire.base.mathlib.MathLib.pow;
// 
// 
// public class CornersFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_XWIDTH = "x";
//   private static final String PARAM_YWIDTH = "y";
//   private static final String PARAM_MULTX = "mult x";
//   private static final String PARAM_MULTY = "mult y";
//   private static final String PARAM_X_POWER = "x power";
//   private static final String PARAM_Y_POWER = "y power";
//   private static final String PARAM_XY_POWER = "xy power add";
//   private static final String PARAM_LOGMODE = "log mode (0/1)";
//   private static final String PARAM_LOG_BASE = "log base";
// 
//   private static final String[] paramNames = {PARAM_XWIDTH, PARAM_YWIDTH, PARAM_MULTX, PARAM_MULTY, PARAM_X_POWER, PARAM_Y_POWER, PARAM_XY_POWER, PARAM_LOGMODE, PARAM_LOG_BASE};
//   private double xwidth = 1.0;
//   private double ywidth = 1.0;
//   private double multx = 1.0;
//   private double multy = 1.0;
//   private double xpower = 0.75;
//   private double ypower = 0.75;
//   private double xypower = 0;
//   private double logmode = 0;
//   private double log_base = 2.71828;
//   private double ex = 0;
//   private double ey = 0;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     // corners by Whittaker Courtney 8-14-2018
// 
//     double xs = pAffineTP.x * pAffineTP.x;
//     double ys = pAffineTP.y * pAffineTP.y;
// 
//     //log mode
//     if (logmode == 0) {
//       ex = pow(xs, xpower + xypower) * multx;
//       ey = pow(ys, ypower + xypower) * multy;
//     } else {
//       ex = pow(log((xs * multx) + 3) / log(log_base), xpower + 2.25 + xypower) - 1.33;
//       ey = pow(log((ys * multy) + 3) / log(log_base), ypower + 2.25 + xypower) - 1.33;
//     }
// 
// 
//     if (pAffineTP.x > 0) {
//       pVarTP.x += pAmount * ex + xwidth;
//     } else {
//       pVarTP.x += pAmount * -ex - xwidth;
//     }
// 
//     if (pAffineTP.y > 0) {
//       pVarTP.y += pAmount * ey + ywidth;
//     } else {
//       pVarTP.y += pAmount * -ey - ywidth;
//     }
//     if (pContext.isPreserveZCoordinate()) {
//       pVarTP.z += pAmount * pAffineTP.z;
//     }
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
//     return new Object[]{xwidth, ywidth, multx, multy, xpower, ypower, xypower, logmode, log_base};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_XWIDTH.equalsIgnoreCase(pName))
//       xwidth = pValue;
//     else if (PARAM_YWIDTH.equalsIgnoreCase(pName))
//       ywidth = pValue;
//     else if (PARAM_MULTX.equalsIgnoreCase(pName))
//       multx = pValue;
//     else if (PARAM_MULTY.equalsIgnoreCase(pName))
//       multy = pValue;
//     else if (PARAM_X_POWER.equalsIgnoreCase(pName))
//       xpower = pValue;
//     else if (PARAM_Y_POWER.equalsIgnoreCase(pName))
//       ypower = pValue;
//     else if (PARAM_XY_POWER.equalsIgnoreCase(pName))
//       xypower = pValue;
//     else if (PARAM_LOGMODE.equalsIgnoreCase(pName))
//       logmode = pValue;
//     else if (PARAM_LOG_BASE.equalsIgnoreCase(pName))
//       log_base = pValue;
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
// 
//   @Override
//   public String getName() {
//     return "corners";
//   }
// 
// }
// 
