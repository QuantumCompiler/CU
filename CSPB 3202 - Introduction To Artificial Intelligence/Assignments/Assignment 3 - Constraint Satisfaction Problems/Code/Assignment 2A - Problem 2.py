sld_providence = dict(
    chi=833,
    cle=531,
    ind=782,
    col=618,
    det=596,
    buf=385,
    pit=458,
    syr=253,
    bal=325,
    phi=236,
    new=157,
    pro=0,
    bos=38,
    por=136)

""" heuristic_sld_providence - Returns the straight-line distance heuristic between the given state (city) and Providence.
    Input:
        state - The current city/state as a string.
    Output:
        The straight-line distance from the given state to Providence as an integer.
"""
def heuristic_sld_providence(state):
    return sld_providence[state]