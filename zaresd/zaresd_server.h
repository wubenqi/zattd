// Copyright (C) 2014 by wubenqi
// Distributable under the terms of either the Apache License (Version 2.0) or 
// the GNU Lesser General Public License, as specified in the COPYING file.
//
// By: wubenqi<wubenqi@gmail.com>
//

#ifndef ZARESD_ZARESD_SERVER_H_
#define ZARESD_ZARESD_SERVER_H_

#include "base2/daemon/base_daemon.h"

class ZAresdServer : public base::BaseDaemon {
public:
  ZAresdServer();
  virtual ~ZAresdServer();

protected:
  // ю╢вт net::BaseDaemon
  virtual int LoadConfig( const base::FilePath& xml_ini_file );
  virtual int	Initialize( int argc, char** argv );
  virtual int Destroy();
};


#endif
