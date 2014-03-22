<?hh
namespace HackMvc;

class Application {

	private array<int, Routing\Route> $routes = array();

	public function __construct()
	{}

	public function get($regex, callable $handler) {
		$this->routes[] = new Routing\RegexRoute(array('GET'), $regex, $handler);
	}

	public function handle(Http\Request $request) 
	{
		foreach ($this->routes as $route) {
			if ($response = $route->match($request)) {
				//todo: create an actual response
				return $response;
			}
		}

		return 'no routes matches';
	}

	private function createResponseFromString()
	{

	}
}
