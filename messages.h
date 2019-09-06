/********************************************************************************
ItVide
Copyright (C) 2017  Henric Zazzi <henric@zazzi.se>

ItVide is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*******************************************************************************/
#ifndef MESSAGES_H
#define MESSAGES_H
//------------------------------------------------------------------------------
// Error Messages
//------------------------------------------------------------------------------
namespace ERROR_TEXT {
  const char DATAMATRIX_NO_INTEGER[]="DataMatrix: Value is not Integer";
  }
//------------------------------------------------------------------------------
namespace STATUS {
  const char FILE_CAPTION[]="Open File";
  const char FILE_FILTER[]="CSV Files (*.csv);;Text Files (*.txt);;All files (*.*)";
  const char TABLE_NAME[]="Table ";
  const char ALL_STRINGS[]="All";
  }
//------------------------------------------------------------------------------
namespace PROPERTIES {
  const char TABLEID[]="tableid";
  const char MATRIXID[]="matrixid";
  }
//------------------------------------------------------------------------------
#endif // MESSAGES_H
