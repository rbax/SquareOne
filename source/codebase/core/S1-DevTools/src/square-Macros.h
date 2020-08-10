#pragma once

#define FOR_I(a) for (int i=0;i<(a);i++)
#define FOR_J(a) for (int j=0;j<(a);j++)

#define FOR_IR(a) for (unsigned i = (a); i-- > 0;)
#define FOR_JR(a) for (unsigned j = (a); j-- > 0;)


#define SQUARE_START extern "C++" { namespace Square {
#define SQUARE_END } }


#define SQUARE_OBJ Square::Objects
#define SQUARE_IO Square::IO

#define SQUARE_TOOLS Square::Tools
#define SQUARE_STYLES Square::Styles
