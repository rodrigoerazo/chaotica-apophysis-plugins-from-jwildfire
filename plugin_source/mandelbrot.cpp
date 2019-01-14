/*
    Apophysis Plugin: mandelbrot

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/MandelbrotFunc.java

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

#include <vector>
using namespace std;


#include "datahelpers.h"



typedef struct
{
	int iter;
	double xmin;
	double xmax;
	double ymin;
	double ymax;
	int invert;
	double skin;
	double cx;
	double cy;
	int max_points;
	int seed;
	double rnd_z_range;
	int _pIdx;
	vector <double> _xP;
	vector <double> _yP;
	vector <double> _zP;
	double _x0;
	double _y0;
	double _z0;

GOODRAND_STRUCT;
} Variables;

#define APO_VARIABLE_PREFIX "mandelbrot_"
#include "plugin.h"

APO_PLUGIN("mandelbrot");
APO_VARIABLES(
	VAR_INTEGER(iter, 100),
	VAR_REAL(xmin, -1.6),
	VAR_REAL(xmax, 1.6),
	VAR_REAL(ymin, -1.2),
	VAR_REAL(ymax, 1.2),
	VAR_INTEGER(invert, 0),
	VAR_REAL(skin, 0),
	VAR_REAL(cx, 0.0),
	VAR_REAL(cy, 0.0),
	VAR_INTEGER(max_points, -1),
	VAR_INTEGER(seed, 1234),
	VAR_REAL(rnd_z_range, 0.0),

);



int PluginVarPrepare(Variation* vp)
{
    GOODRAND_PREPARE();
    VAR(_x0) = VAR(_y0) = VAR(_z0) = 0.0;
    VAR(_xP).clear();
    VAR(_yP).clear();
    VAR(_zP).clear();
    VAR(_pIdx) = 0;
    
    GOODRAND_SEED(VAR(seed));

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    double x1 = VAR(_x0);
    double x = VAR(_x0);
    double y1 = VAR(_y0);
    double y = VAR(_y0);
    int currIter;

    bool inverted = GOODRAND_01() < VAR(invert);
    if (inverted) {
      currIter = 0;
    } else {
      currIter = VAR(iter);
    }
    while ((inverted && (currIter < VAR(iter))) ||
            ((!inverted) && ((currIter >= VAR(iter)) ||
                    ((VAR(skin) < 1) && (currIter < 0.1 * VAR(iter) * (1 - VAR(skin))))))) {
      if ((VAR(_x0) == 0) && (VAR(_y0) == 0)) {
        // Choose a point at random
        if (VAR(max_points) > 0) {
          if (VAR(_xP).size() >= VAR(max_points)) {
            VAR(_x0) = VAR(_xP).at(VAR(_pIdx));
            VAR(_y0) = VAR(_yP).at(VAR(_pIdx));
            VAR(_z0) = VAR(_zP).at(VAR(_pIdx)++);
            if (VAR(_pIdx) >= VAR(max_points)) {
              VAR(_pIdx) = 0;
            }
          } else {
            VAR(_x0) = (VAR(xmax) - VAR(xmin)) * GOODRAND_01() + VAR(xmin);
            VAR(_y0) = (VAR(ymax) - VAR(ymin)) * GOODRAND_01() + VAR(ymin);
            VAR(_z0) = GOODRAND_01() * VAR(rnd_z_range);
            VAR(_xP).emplace_back(VAR(_x0));
            VAR(_yP).emplace_back(VAR(_y0));
            VAR(_zP).emplace_back(VAR(_z0));
          }
        } else {
          VAR(_x0) = (VAR(xmax) - VAR(xmin)) * GOODRAND_01() + VAR(xmin);
          VAR(_y0) = (VAR(ymax) - VAR(ymin)) * GOODRAND_01() + VAR(ymin);
          VAR(_z0) = GOODRAND_01() * VAR(rnd_z_range);
        }
      } else {
        // Choose a point close to previous point
        VAR(_x0) = (VAR(skin) + 0.001) * (GOODRAND_01() - 0.5) + VAR(_x0);
        VAR(_y0) = (VAR(skin) + 0.001) * (GOODRAND_01() - 0.5) + VAR(_y0);
        //        VAR(_z0) = (VAR(skin) + 0.001) * (GOODRAND_01() - 0.5) + VAR(_z0);
      }
      x1 = VAR(_x0);
      y1 = VAR(_y0);
      x = VAR(_x0);
      y = VAR(_y0);
      currIter = 0;
      while (((x * x + y * y < 2 * 2) && (currIter < VAR(iter)))) {
        double xtemp = x * x - y * y + VAR(_x0);
        y = 2.0 * x * y + VAR(_y0);
        x = xtemp;
        currIter++;
      }
      if ((currIter >= VAR(iter)) || (VAR(skin) == 1) || (currIter < 0.1 * (VAR(iter) * (1 - VAR(skin))))) {
        // Random point next time
        VAR(_x0) = 0;
        VAR(_y0) = 0;
      }
    }
    FPx += VVAR * (x1 + VAR(cx) * x); // + FTx^;
    FPy += VVAR * (y1 + VAR(cy) * y); // + FTy^;
    FPz += VAR(_z0);


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
// 
// // Variation Plugin DLL for Apophysis
// //  Jed Kelsey, 20 June 2007
// package org.jwildfire.create.tina.variation;
// 
// import org.jwildfire.base.Tools;
// import org.jwildfire.create.tina.base.Layer;
// import org.jwildfire.create.tina.base.XForm;
// import org.jwildfire.create.tina.base.XYZPoint;
// import org.jwildfire.create.tina.random.AbstractRandomGenerator;
// import org.jwildfire.create.tina.random.MarsagliaRandomGenerator;
// 
// import java.util.ArrayList;
// import java.util.List;
// 
// public class MandelbrotFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_ITER = "iter";
//   private static final String PARAM_XMIN = "xmin";
//   private static final String PARAM_XMAX = "xmax";
//   private static final String PARAM_YMIN = "ymin";
//   private static final String PARAM_YMAX = "ymax";
//   private static final String PARAM_INVERT = "invert";
//   private static final String PARAM_SKIN = "skin";
//   private static final String PARAM_CX = "cx";
//   private static final String PARAM_CY = "cy";
//   private static final String PARAM_MAX_POINTS = "max_points";
//   private static final String PARAM_SEED = "seed";
//   private static final String PARAM_RND_Z_RANGE = "rnd_z_range";
// 
//   private static final String[] paramNames = {PARAM_ITER, PARAM_XMIN, PARAM_XMAX, PARAM_YMIN, PARAM_YMAX, PARAM_INVERT, PARAM_SKIN, PARAM_CX, PARAM_CY, PARAM_MAX_POINTS, PARAM_SEED, PARAM_RND_Z_RANGE};
// 
//   private int iter = 100;
//   private double xmin = -1.6;
//   private double xmax = 1.6;
//   private double ymin = -1.2;
//   private double ymax = 1.2;
//   private int invert = 0;
//   private double skin = 0;
//   private double cx = 0.0;
//   private double cy = 0.0;
//   private int max_points = -1;
//   private int seed = 1234;
//   private double rnd_z_range = 0.0;
// 
//   private AbstractRandomGenerator randGen;
// 
//   private int _pIdx = 0;
//   private List<Double> xP = new ArrayList<Double>();
//   private List<Double> yP = new ArrayList<Double>();
//   private List<Double> zP = new ArrayList<Double>();
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     double x1 = _x0;
//     double x = _x0;
//     double y1 = _y0;
//     double y = _y0;
//     int currIter;
// 
//     boolean inverted = randGen.random() < this.invert;
//     if (inverted) {
//       currIter = 0;
//     } else {
//       currIter = iter;
//     }
//     while ((inverted && (currIter < iter)) ||
//             ((!inverted) && ((currIter >= iter) ||
//                     ((skin < 1) && (currIter < 0.1 * iter * (1 - skin)))))) {
//       if ((_x0 == 0) && (_y0 == 0)) {
//         // Choose a point at random
//         if (max_points > 0) {
//           if (xP.size() >= max_points) {
//             _x0 = xP.get(_pIdx);
//             _y0 = yP.get(_pIdx);
//             _z0 = zP.get(_pIdx++);
//             if (_pIdx >= max_points) {
//               _pIdx = 0;
//             }
//           } else {
//             _x0 = (xmax - xmin) * randGen.random() + xmin;
//             _y0 = (ymax - ymin) * randGen.random() + ymin;
//             _z0 = randGen.random() * rnd_z_range;
//             xP.add(_x0);
//             yP.add(_y0);
//             zP.add(_z0);
//           }
//         } else {
//           _x0 = (xmax - xmin) * randGen.random() + xmin;
//           _y0 = (ymax - ymin) * randGen.random() + ymin;
//           _z0 = randGen.random() * rnd_z_range;
//         }
//       } else {
//         // Choose a point close to previous point
//         _x0 = (skin + 0.001) * (randGen.random() - 0.5) + _x0;
//         _y0 = (skin + 0.001) * (randGen.random() - 0.5) + _y0;
//         //        _z0 = (skin + 0.001) * (randGen.random() - 0.5) + _z0;
//       }
//       x1 = _x0;
//       y1 = _y0;
//       x = _x0;
//       y = _y0;
//       currIter = 0;
//       while (((x * x + y * y < 2 * 2) && (currIter < iter))) {
//         double xtemp = x * x - y * y + _x0;
//         y = 2.0 * x * y + _y0;
//         x = xtemp;
//         currIter++;
//       }
//       if ((currIter >= iter) || (skin == 1) || (currIter < 0.1 * (iter * (1 - skin)))) {
//         // Random point next time
//         _x0 = 0;
//         _y0 = 0;
//       }
//     }
//     pVarTP.x += pAmount * (x1 + cx * x); // + FTx^;
//     pVarTP.y += pAmount * (y1 + cy * y); // + FTy^;
//     pVarTP.z += _z0;
//   }
// 
//   @Override
//   public String[] getParameterNames() {
//     return paramNames;
//   }
// 
//   @Override
//   public Object[] getParameterValues() {
//     return new Object[]{iter, xmin, xmax, ymin, ymax, invert, skin, cx, cy, max_points, seed, rnd_z_range};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_ITER.equalsIgnoreCase(pName))
//       iter = Tools.FTOI(pValue);
//     else if (PARAM_XMIN.equalsIgnoreCase(pName))
//       xmin = pValue;
//     else if (PARAM_XMAX.equalsIgnoreCase(pName))
//       xmax = pValue;
//     else if (PARAM_YMIN.equalsIgnoreCase(pName))
//       ymin = pValue;
//     else if (PARAM_YMAX.equalsIgnoreCase(pName))
//       ymax = pValue;
//     else if (PARAM_INVERT.equalsIgnoreCase(pName))
//       invert = Tools.FTOI(pValue);
//     else if (PARAM_SKIN.equalsIgnoreCase(pName))
//       skin = pValue;
//     else if (PARAM_CX.equalsIgnoreCase(pName))
//       cx = pValue;
//     else if (PARAM_CY.equalsIgnoreCase(pName))
//       cy = pValue;
//     else if (PARAM_MAX_POINTS.equalsIgnoreCase(pName)) {
//       max_points = Tools.FTOI(pValue);
//       if (max_points > 0 && max_points < 100) {
//         max_points = 100;
//       }
//     } else if (PARAM_SEED.equalsIgnoreCase(pName))
//       seed = Tools.FTOI(pValue);
//     else if (PARAM_RND_Z_RANGE.equalsIgnoreCase(pName))
//       rnd_z_range = pValue;
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "mandelbrot";
//   }
// 
//   private double _x0, _y0, _z0;
// 
//   @Override
//   public void init(FlameTransformationContext pContext, Layer pLayer, XForm pXForm, double pAmount) {
//     _x0 = _y0 = _z0 = 0.0;
//     xP.clear();
//     yP.clear();
//     zP.clear();
//     _pIdx = 0;
//     randGen = new MarsagliaRandomGenerator();
//     randGen.randomize(seed);
//   }
// 
// }
// 
