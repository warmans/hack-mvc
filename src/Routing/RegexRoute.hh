<?hh
namespace HackMvc\Routing;
use HackMvc\Http;

class RegexRoute extends AbstractRoute
{
    public function match(Http\Request $request): \mixed
    {
        foreach ($this->methods as $method) {
            if ($request->getMethod() === $method) {
                $matches = array();
                if (preg_match($this->regex, $request->getUri()->getPath(), $matches)) {
                    return new RouteMatch($this, $request, $matches);
                }
            }
        }
        return false;
    }
}
