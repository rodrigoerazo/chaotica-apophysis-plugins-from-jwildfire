/*
    Apophysis Plugin

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

//

	-square by bezo97, 2017 09, the square plugin rewritten, because we didn't have the source :)

*/

typedef struct {
	double x;
	double y;
	double z;
} double3;

typedef struct {

} Variables;

#include "apoplugin.h"

APO_PLUGIN("square");
APO_VARIABLES(

);

int PluginVarPrepare(Variation* vp)
{
    //no preps, problem?
    return 1;
}

int PluginVarCalc(Variation* vp)
{
	*(vp->pFPx) = (random01()-0.5)*VVAR;
	*(vp->pFPy) = (random01()-0.5)*VVAR;
    return 1;
}
