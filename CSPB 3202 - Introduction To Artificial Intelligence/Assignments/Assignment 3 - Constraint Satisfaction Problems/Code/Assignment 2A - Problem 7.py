from collections import OrderedDict

canada = OrderedDict(
    [("AB"  , ["BC","NT","SK"]),
    ("BC" , ["AB","NT","YT"]),
    ("LB" , ["NF", "NS", "PE","QC"]),
    ("MB" , ["ON","NV","SK"]),
    ("NB" , ["NS","QC"]),
    ("NF" , ["LB","QC"]),
    ("NS" , ["LB","NB","PE"]),
    ("NT" , ["AB","BC","NV","SK","YT"]),
    ("NV" , ["MB","NT"]),
    ("ON" , ["MB","QC"]),
    ("PE" , ["LB","NS","QC"]),
    ("QC" , ["LB","NB","NF","ON","PE"]),  
    ("SK" , ["AB","MB","NT"]),
    ("YT" , ["BC","NT"])])
    
states = ["AB", "BC", "LB", "MB", "NB", "NF", "NS", "NT", "NV", "ON", "PE", "QC", "SK", "YT"]
colors = ["blue", "green", "red"]

class CSP:
    # your code here#
    """ Constructor - Creates an instance of the CSP class
        Input:
            variables - These are the variables of the CSP
            neighbors - These are the neighbors of a given variable
            domain - The domain of the variables in the CSP
        Algorithm:
            * Create instances for variables, neighbors, and domain from the constructor
        Output:
            This function does not return a value
    """
    def __init__(self, variables, neighbors, domain):
        self.variables = variables
        self.neighbors = neighbors
        self.domain = {var: domain for var in variables}

cspObj = CSP(states,canada,colors)