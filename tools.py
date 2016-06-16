# -*- coding: utf-8 -*-

#      ____ __     ____   ___    ____ __         (((((()
#     | |_  \ \  /   ) ) | |  ) | |_  \ \  /  \(@)- /
#     |_|__  \_\/  __)_) |_|_/  |_|__  \_\/   /(@)- \
#                                                ((())))

import os, re

def clip_h( fn ):

    M_CUT      = '* \\{'
    RE_CUT     = re.compile( r'^\s*\*\s*\\\{' )

    M_CUT_END  = '/** \\} */'
    RE_CUT_END = re.compile( r'^\s*/\*\*\s*\\\}\s*\*/' )

    M_IMPORT   = '($import "%sev3_'

    try:
        with open( fn, 'r' ) as f:
            txt = f.readlines()
    except:
        raise Exception( '* ERROR * File "%s" not found.' % ( fn ))

    b = 0;
    for i, ln in enumerate( txt ):
        if not b:
#           Cut from the 2nd line after
#           * \{
            if RE_CUT.match( ln ):
                b = i + 2
        else:
#           ... up to
#           /** \} */
            if RE_CUT_END.match( ln ):
                e = i
                break
    else:
        raise Exception( '* ERROR * File "%s": label "%s" not found.' % ( fn, M_CUT if not b else M_CUT_END ))

#   ... and add the directory name to each ($import) of 'ev3_' files.
    return ''.join( txt[ b : e ]).replace( M_IMPORT % ( '' ), M_IMPORT % ( os.path.dirname( fn ) + '/' ))
