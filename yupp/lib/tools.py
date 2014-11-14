import os

M_CUT = ' *  \\{\n'
M_CUT_END = '/** \\} */\n'
M_IMPORT1 = '($import "%sev3_'
M_IMPORT2 = '($import "%snxt_'
E1 = '* ERROR * File %s: label "%s" not found.'
E2 = '* ERROR * File %s not found.'

def clip_h( fn ):
    try:
        f = open( fn, 'r' )
    except:
        raise Exception( E2 % ( fn ))

    t = f.readlines()
    f.close()

    try:
        b = t.index( M_CUT )
    except:
        raise Exception( E1 % ( fn, M_CUT[ :-1 ]))

    try:
        e = t.index( M_CUT_END, b + 1 )
    except:
        raise Exception( E1 % ( fn, M_CUT_END[ :-1 ]))

    a = ''.join( t[ b + 2 : e ])
    d = os.path.dirname( fn ) + '/'
    a = a.replace( M_IMPORT1 % ( '' ), M_IMPORT1 % ( d ))
    a = a.replace( M_IMPORT2 % ( '' ), M_IMPORT2 % ( d ))

    return a
