<?hh
namespace HackMvc\Routing;
use HackMvc\Http;

abstract class AbstractRoute
{
    public function __construct(protected array<string> $methods, protected \string $regex, protected \mixed $handler) 
    {}

    public function getHandler(): mixed
    {
        return $this->handler;
    }

    abstract public function match(Http\Request $request);
}