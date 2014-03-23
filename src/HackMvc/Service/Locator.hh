<?hh
namespace HackMvc\Service;

class Locator 
{
    private array<string, mixed> $factories = array();
    private array<sting, mixed> $services = array();

	public function registerFactory(\string $name, callable $factory): void 
    {
        if ($this->factoryExists($name)) {
            throw new \RuntimeException("Duplicate factory name was registered: $name");
        }
        $this->factories[$name] = $factory;
    }

    public function registerService(\string $name, mixed $service): void
    {
        if ($this->serviceExists($name)) {
            throw new \RuntimeException("Duplicate service name was registered: $name");
        }
        $this->services[$name] = $service;
    }

    public function getService(\string $name): mixed
    {
        if (!$this->serviceExists($name)) {
            if ($this->factoryExists($name)) {
                $factory = $this->factories[$name];
                $this->services[$name] = call_user_func($factory, $this);
            } else {
                throw new \RuntimeException("Unable to locate service: $name");
            }
        }
        return $this->services[$name];
    }

    public function serviceExists(\string $name): bool
    {
        return array_key_exists($name, $this->services);
    }

    public function factoryExists(\string $name): sbool
    {
        return array_key_exists($name, $this->factories);
    }
}
