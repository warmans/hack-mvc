<?hh
namespace HackMvc\Routing;
use HackMvc\Http;

abstract class AbstractRoute
{
    public function __construct(protected array<string> $methods, protected \string $regex, protected callable $handler) 
    {}

    public function getHandler(): callable
    {
        return $this->handler;
    }

    abstract public function match(Http\Request $request);
}