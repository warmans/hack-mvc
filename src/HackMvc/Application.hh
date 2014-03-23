<?hh
namespace HackMvc;

class Application {

    private array<int, Routing\Route> $routes = array();

    public function __construct(private ?Service\Locator $service_locator)
    {}

    /**
    * HTTP GET Handler
    */
    public function get($regex, callable $handler) {
        $this->routes[] = new Routing\RegexRoute(array('GET'), $regex, $handler);
    }

    /**
    * HTTP POST Handler
    */
    public function post($regex, callable $handler) {
        $this->routes[] = new Routing\RegexRoute(array('POST'), $regex, $handler);
    }

    /**
    * HTTP PUT Handler
    */
    public function put($regex, callable $handler) {
        $this->routes[] = new Routing\RegexRoute(array('PUT'), $regex, $handler);
    }

    /**
    * HTTP DELETE Handler
    */
    public function delete($regex, callable $handler) {
        $this->routes[] = new Routing\RegexRoute(array('DELETE'), $regex, $handler);
    }

    /**
    * HTTP OPTIONS Handler
    */
    public function options($regex, callable $handler) {
        $this->routes[] = new Routing\RegexRoute(array('OPTIONS'), $regex, $handler);
    }

    /**
    * HTTP HEAD Handler
    */
    public function head($regex, callable $handler) {
        $this->routes[] = new Routing\RegexRoute(array('HEAD'), $regex, $handler);
    }

    /**
    * HTTP TRACE Handler
    */
    public function trace($regex, callable $handler) {
        $this->routes[] = new Routing\RegexRoute(array('TRACE'), $regex, $handler);
    }

    /**
    * HTTP CONNECT Handler
    */
    public function connect($regex, callable $handler) {
        $this->routes[] = new Routing\RegexRoute(array('CONNECT'), $regex, $handler);
    }

    /**
    * Handler for other/multiple HTTP verbs
    */
    public function handler(array<string> $methods, $regex, callable $handler) {
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
                return $this->createResponse(call_user_func($handler, $match, $this->service_locator));
            }
        }
        return new Http\Response(new Http\Status(404), new \Map(), 'no routes matches');
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
