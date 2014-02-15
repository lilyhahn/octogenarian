#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
std::string encode( const std::string & to_encode ) {
   std::string::size_type found = 0 , nextfound = 0 ;
   std::ostringstream oss ;
   nextfound = to_encode.find_first_not_of( to_encode[ found ] , found ) ;
   while ( nextfound != std::string::npos ) {
      if(nextfound - found > 1)
         oss << nextfound - found ;
      oss << to_encode[ found ] ;
      found = nextfound ;
      nextfound = to_encode.find_first_not_of( to_encode[ found ] , found ) ;
   }
   //since we must not discard the last characters we add them at the end of the string
   std::string rest ( to_encode.substr( found ) ) ;//last run of characters starts at position found 
   oss << rest.length( ) << to_encode[ found ] ;
   return oss.str( ) ;
}