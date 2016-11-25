---
Usage: transit
	 -r: ftpserver's ip or hostname
	 -k: ftpserver's username and password
	     (default: anonymous:anonymous)
	 -d: run in daemon
	 -x: open log, see in /var/log/message, depends on syslog.conf
	     (defalut: close)
	 -D: all json fils keep in this dir, include config file.
	please see the sample in /appfs/etc/transit_dir/*
	     (defalut: /tmp/)
	     filename: CONFIG (!!this is config file)
	               WLRZ FJGJ JSTX XWRZ SJRZ
	               PTNR SGJZ CSZL CSZT SBZL
	               JSJZT SBGJ RZSJ SJTZ PNFJ
Example:./transit -d -k aaa:123 -r 10.1.1.1 -D /tmp/
---
