from xmlrpc.server import SimpleXMLRPCServer
from xmlrpc.server import SimpleXMLRPCRequestHandler
import xmlrpc.client

print("Proces3")

# Restrict to a particular path.
class RequestHandler(SimpleXMLRPCRequestHandler):
    rpc_paths = ('/RPC2',)

# Create server
server = SimpleXMLRPCServer(('localhost', 10003),requestHandler=RequestHandler)
server.register_introspection_functions()

# Register pow() function; this will use the value of
# pow.__name__ as the name, which is just 'pow'.
server.register_function(pow)

# # Register a function under a different name
# def adder_function(x, y):
#     return x + y
# server.register_function(adder_function, 'add')

# Register an instance; all the methods of the instance are
# published as XML-RPC methods (in this case, just 'mul').

class post:
    def post(self,x):
        print ("Proces3 Wita sie i przesyla wiadomosc dalej") 
        print(x)
        wyslij(x)
   

def wyslij(x):
    s = xmlrpc.client.ServerProxy('http://127.0.0.1:10004')
    #print(s.system.listMethods())
    s.Demo.addNumbers(x)
    #print(s.system.listMethods())



server.register_instance(post())

# Run the server's main loop
server.serve_forever()
