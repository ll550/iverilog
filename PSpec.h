#ifndef __PSpec_H
#define __PSpec_H
/*
 * Copyright (c) 2006 Stephen Williams <steve@icarus.com>
 *
 *    This source code is free software; you can redistribute it
 *    and/or modify it in source code form under the terms of the GNU
 *    General Public License as published by the Free Software
 *    Foundation; either version 2 of the License, or (at your option)
 *    any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA
 */
#ifdef HAVE_CVS_IDENT
#ident "$Id: PSpec.h,v 1.2 2007/02/12 01:52:21 steve Exp $"
#endif

# include  "LineInfo.h"
# include  "StringHeap.h"
# include  <vector>

class PExpr;

/*
* The PSpecPath is the parse of a specify path, which is in its most
* general form <path> = <delays>. The <delays> are collected into the
* "delays" vector in all cases, and the variety is in the other
* members.
*
* All paths also have a list of source names in the src vector, and a
* list of destination names in the dst vector. These pairs are the
* actual paths.
*
* If the path is a simple path, then:
*      condition == nil
*      edge == 0
*      data_source_expression == nil
*
* If the path is conditional, then conditional == true and condition
* is the condition expression. If the condition expression is nil,
* then this is an ifnone conditional path.
*
* If edge != 0, then the path is edge sensitive and the optional
* data_source_expression may be present.
*/
class PSpecPath  : public LineInfo {

    public:
      PSpecPath(unsigned src_cnt, unsigned dst_cnt);
      ~PSpecPath();

      void elaborate(class Design*des, class NetScope*scope) const;

      void dump(std::ostream&out, unsigned ind) const;

    public:
	// Condition expression, if present.
      bool conditional;
      class PExpr* condition;
	// Edge specification (-1==negedge, 0 = no edge, 1==posedge)
      int edge;
	// Ordered set of source nodes of a path
      std::vector<perm_string> src;
	// Ordered set of destination nodes of a path
      std::vector<perm_string> dst;
	// Data source expression
      class PExpr* data_source_expression;

      std::vector<class PExpr*>delays;
};

#endif
