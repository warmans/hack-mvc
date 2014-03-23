<?hh
namespace HackMvc\Routing;
use HackMvc\Http;

class RouteMatch
{
    public function __construct(private AbstractRoute $route, private Http\Request $request, private array $matched_substrings) 
    {}

    public function getRoute(): AbstractRoute 
    {
        return $this->route;
    }

    public function getRequest(): Http\Request
    {
        return $this->request;
    }

    public function getMatchedSubstrings(): array
    {
        return $this->matched_substrings;
    }
}
