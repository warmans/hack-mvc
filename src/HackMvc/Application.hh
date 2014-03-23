<?hh
namespace HackMvc;

class Application {

    private array<int, Routing\Route> $routes = array();

    public function __construct(private ?Service\Locator $service_locator)
    {}

    public function get($regex, callable $handler) {
        $this->routes[] = new Routing\RegexRoute(array('GET'), $regex, $handler);
    }

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
