<?hh
namespace HackMvc;

class Application {

    private array<int, Routing\Route> $routes = array();

    public function __construct(private ?Service\Locator $service_locator)
    {}

    /**
    * HTTP GET Handler
    */
    public function get($regex, \mixed $handler) {
        $this->routes[] = new Routing\RegexRoute(array('GET'), $regex, $handler);
    }

    /**
    * HTTP POST Handler
    */
    public function post($regex, \mixed $handler) {
        $this->routes[] = new Routing\RegexRoute(array('POST'), $regex, $handler);
    }

    /**
    * HTTP PUT Handler
    */
    public function put($regex, \mixed $handler) {
        $this->routes[] = new Routing\RegexRoute(array('PUT'), $regex, $handler);
    }

    /**
    * HTTP DELETE Handler
    */
    public function delete($regex, \mixed $handler) {
        $this->routes[] = new Routing\RegexRoute(array('DELETE'), $regex, $handler);
    }

    /**
    * HTTP OPTIONS Handler
    */
    public function options($regex, \mixed $handler) {
        $this->routes[] = new Routing\RegexRoute(array('OPTIONS'), $regex, $handler);
    }

    /**
    * HTTP HEAD Handler
    */
    public function head($regex, \mixed $handler) {
        $this->routes[] = new Routing\RegexRoute(array('HEAD'), $regex, $handler);
    }

    /**
    * HTTP TRACE Handler
    */
    public function trace($regex, \mixed $handler) {
        $this->routes[] = new Routing\RegexRoute(array('TRACE'), $regex, $handler);
    }

    /**
    * HTTP CONNECT Handler
    */
    public function connect($regex, \mixed $handler) {
        $this->routes[] = new Routing\RegexRoute(array('CONNECT'), $regex, $handler);
    }

    /**
    * Handler for other/multiple HTTP verbs
    */
    public function handler(array<string> $methods, $regex, \mixed $handler) {
        $this->routes[] = new Routing\RegexRoute($methods, $regex, $handler);
    }

    /**
    * Handle a request
    */
    public function handle(Http\Request $request) 
    {
        foreach ($this->routes as $route) {
            if ($match = $route->match($request)) {
                $handler = $match->getRoute()->getHandler();
                return $this->createResponse(
                    call_user_func($this->convertHandlerToCallable($handler), $match, $this->service_locator)
                ); 
            }
        }
        return new Http\Response(new Http\Status(404), new \Map(), 'no routes matches');
    }

    private function convertHandlerToCallable(\mixed $handler)
    {
        switch (true) {
            
            case is_callable($handler):
                return $handler;

            case $handler instanceof \Pair:
                return array($this->service_locator->getService($handler[0]), $handler[1]);        
        }

        throw new \RuntimeException('Unknown handler type');
    }

    private function createResponse(\mixed $handler_response)
    {
        switch (true) {
            case $handler_response instanceof Http\Response:
                //handler returned a response - nothing to do
                return $handler_response;
            case is_string($handler_response):
                //handler returned a string - assume success and return as response
                return new Http\Response(new Http\Status(200), new \Map(), $handler_response);
        }

        throw new \RuntimeException('Unexpected response from handler. Should be string or Response');
    }
}
