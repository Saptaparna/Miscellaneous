// 
#include "BTagTest/BTagSoftLeptonAnalyzer/interface/RooGKCounter.h"

#include <iostream>
#include <math.h>
using std::cout;
using std::endl;
using std::ostream;

//ClassImp(RooGKCounter)

RooGKCounter::RooGKCounter(){
  init();
} 

RooGKCounter::RooGKCounter( const char *message ){
  init();
  _message = message;
  if ( _message . length() == 0 ) printCount = false;
} 

RooGKCounter::RooGKCounter( unsigned long int theFirst, unsigned long int theDivider ){
  init();
  _count = theFirst;
  _firstCount = theFirst;
  _divider = theDivider;
  printCount = true;
} 

void RooGKCounter::setCounter( unsigned long int theCount ){
  _count = theCount;
}

void RooGKCounter::setDivider( unsigned int theDivider ){
  _divider = theDivider;
}

void RooGKCounter::setPrintCount( bool _printCount ){
  printCount = _printCount;
}

void RooGKCounter::setNewLine( bool newLine ){
  _newLine = newLine;
}

void RooGKCounter::setMessage( const char *message ){
  _message = message;
}

void RooGKCounter::init( void ){
  _count = 0;
  _count_double_type = 0.0;
  _firstCount = 0;
  _divider = 1;
  printCount = false;
  firstCountEntry = true;
  _message = "processing entry #";
  _newLine = true;

  initTime = time( NULL );
  firstTickTime = 1;
  lastTickTime = 1;
  lastPrintTime = 1;

}

void RooGKCounter::count( void ){

  _count++;

  double _number;
  double _freq;
  double _limit = 1./(double)_divider;

  _number = (double)_count;
  _freq = (double)_divider;

  if (firstCountEntry){
    if ( printCount ) cout << "Counter is on:" << endl;
    firstCountEntry = false;
    firstTickTime = time( NULL );
  }

  if ( printCount ){
    if ( fmod( _number, _freq ) < _limit ){
      double averageTimeSinceLastPrint = 0.0;
      double averageTimeSinceFirstTick = 0.0;
      if ( lastPrintTime > 1 )
	{
	  averageTimeSinceLastPrint = ( time( NULL ) - lastPrintTime ) / (double)_divider;
	}
      if ( _count > _firstCount )
	{
	  averageTimeSinceFirstTick = ( time( NULL ) - firstTickTime ) / (double)( _count - _firstCount );
	}
      if ( !_newLine )
	{
	  cout << char(13) << _message . c_str() << _count;
	  if ( _count > _firstCount ) cout << ", average time per count, sec: " << averageTimeSinceFirstTick;
	  fflush(stdout);
	}
      else
	{
	  cout << _message . c_str() << _count;
	  if ( _count > _firstCount ) cout << ", average time per count, sec: " << averageTimeSinceFirstTick;
	  cout << endl;
	}
      lastPrintTime = time( NULL );
    }
  }
  
  lastTickTime = time( NULL );
}

unsigned long int RooGKCounter::getCount( void ){
  return _count;
}

double RooGKCounter::getCountDouble( void ){
  return _count_double_type;
}

void RooGKCounter::increment( long int _incr ){
  _count += _incr;
}

void RooGKCounter::incrementDouble( double _incr ){
  _count_double_type += _incr;
}

RooGKCounter::~RooGKCounter(){
}
