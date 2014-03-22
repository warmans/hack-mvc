<?hh

namespace HackMvc\Routing;
use HackMvc\Http;

class RegexRoute
{
	public function __construct(private array<string> $methods, private \string $regex, private callable $handler) 
	{}

	public function match(Http\Request $request)
	{
		foreach ($this->methods as $method) {
			$matches = array();
			if (preg_match($this->regex, $request->getUri()->getPath(), $matches)) {
				$handler = $this->handler;
				return $handler($matches);
			}
		}
		return false;
	}
}