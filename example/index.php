<?hh
spl_autoload_register(function ($class) {

    // project-specific namespace prefix
    $prefix = '';

    // base directory for the namespace prefix
    $base_dir = __DIR__ . '/../src/';
    // does the class use the namespace prefix?
    $len = strlen($prefix);
    if (strncmp($prefix, $class, $len) !== 0) {
        // no, move to the next registered autoloader
        return;
    }
    
    // get the relative class name
    $relative_class = substr($class, $len);

    // replace the namespace prefix with the base directory, replace namespace
    // separators with directory separators in the relative class name, append
    // with .php
    $file = $base_dir . str_replace('\\', '/', $relative_class) . '.hh';
    // if the file exists, require it
    if (file_exists($file)) {
        require $file;
    }
});


echo '<pre>';

$globals = new \HackMvc\Php\Globals();
$request = $globals->getHttpRequest();

$sl = new HackMvc\Service\Locator();
$app = new HackMvc\Application($sl);

$app->get('#.+#', function(HackMvc\Routing\RouteMatch $route_match, HackMvc\Service\Locator $service_locator) { 
    return new \HackMvc\Http\Response(new \HackMvc\Http\Status(200), new \Map(array('x-some-header'=>'blah')), 'foo'); 
});

$response = $app->handle($request);
$response->flush();
