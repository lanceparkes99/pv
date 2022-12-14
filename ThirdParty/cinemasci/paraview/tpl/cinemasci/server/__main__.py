import http.server
import socketserver
from urllib.parse import urlparse
from urllib.parse import parse_qs
# from os import path
# from os.path import relpath
# from os import getcwd
# from os import access
# from os import R_OK

from . import run_cinema_server

if __name__ == "__main__":
    import argparse

    parser = argparse.ArgumentParser(description="run a Cinema Viewer")
    parser.add_argument("--databases", required=True, nargs="+", default=None, help="database to view (required)") 
    parser.add_argument("--viewer", 
                            type=str,
                            choices={"view", "explorer"},
                            required=True, 
                            default="view", 
                            help="viewer type to use. One of [explorer, view] (required)") 
    parser.add_argument("--assetname", default=None, help="asset name to use (optional)") 
    parser.add_argument("--port", type=int, default=8000, help="port to use (optional)") 
    parser.add_argument("--rundir", default=".", help="directory in which to run the server") 
    parser.add_argument("--verbose", action="store_true", help="verbose reporting flag") 
    parser.add_argument("--silent", action="store_true", help="don't report") 
    args = parser.parse_args()

    if (args.databases is None):
        print("Error")
    else:
        run_cinema_server(args.viewer, args.rundir, args.databases, args.port, args.assetname, args.verbose, args.silent)
