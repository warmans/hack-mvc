<?hh
namespace HackMvc\View;

class PhpTemplate 
{
    public function __construct(private \string $template_file, private array $vars = array()) 
    {}

    public function __toString(): \string 
    {
        return $this->render();
    }

    public function __set(\string $name, \mixed $value): \void 
    {
        $this->vars[$name] = $value;
    }

    public function __get(\string $name): \mixed
    {
        return isset($this->vars[$name]) ? $this->vars[$name] : null;
    }

    public function partial(\string $template_file, array $vars = array()): \PhpTemplate
    {
        return new static($template_file, $vars);
    }

    public function render(): \string 
    {
        ob_start();
        require($this->template_file);
        return (string)ob_get_clean();
    }
}
