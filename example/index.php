<?hh
require_once(__DIR__.'/../src/ClassLoader.hh');

$class_loader = new HackMvc\ClassLoader();
$class_loader->addNamespace('HackMvc', __DIR__ . '/../src/');
$class_loader->register();

$globals = new HackMvc\Php\Globals();
$request = $globals->getHttpRequest();

$sl = new \HackMvc\Service\Locator();

//register a class-based controller
$sl->registerFactory('controller.bar', function(\HackMvc\Service\Locator $sl) {
    require_once(__DIR__.'/controller/MyController.hh');
    return new \MyController();
});

$app = new HackMvc\Application($sl);

//closure e.g. index.php/hello/world
$app->get('#/hello(/(?<name>.+))?$#', function(HackMvc\Routing\RouteMatch $route_match, HackMvc\Service\Locator $service_locator) { 
    
    //get matches from URI
    $matches = $route_match->getMatchedSubstrings();

    //return a new response
    return new \HackMvc\Http\Response(
        new \HackMvc\Http\Status(200), 
        new \Map(array('x-some-header'=>'blah')), 
        'hello '.(isset($matches['name']) ? $matches['name'] : 'whoever')
    ); 
});

//controller
$app->get('#/bar$$#', \Pair {'controller.bar', 'barAction'});

//view
$app->get('#/baz$#', function(HackMvc\Routing\RouteMatch $route_match, HackMvc\Service\Locator $service_locator) { 
    //return a sting via a Php Template
    return (string) new \HackMvc\View\PhpTemplate(__DIR__.'/view/example.phtml');
});

$response = $app->handle($request);
$response->flush();
