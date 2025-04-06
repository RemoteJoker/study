springboot 是基于 springframework 的快速开发框架

项目结构如下:
src/
├── main/
│   ├── java/
│   │   └── com/example/demo/
│   │       ├── DemoApplication.java     # 主启动类
│   │       ├── controller/              # 控制器层
│   │       ├── service/                 # 业务逻辑层
│   │       └── repository/              # 数据访问层
│   └── resources/
│       ├── static/                      # 静态资源（JS/CSS）
│       ├── templates/                   # 模板文件（Thymeleaf）
│       └── application.properties       # 配置文件
└── test/                                # 测试代码


@RestController	声明 RESTful 控制器	@RestController public class UserController {}
@RequestMapping	映射请求路径	    @RequestMapping("/api/users")
@GetMapping	    处理 GET 请求	    @GetMapping("/{id}")
@PostMapping	处理 POST 请求	    @PostMapping("/create")
@RequestBody	接收 JSON 请求体	public User create(@RequestBody User user)
@ResponseBody	返回 JSON 响应（已由 @RestController 包含）	@ResponseBody public User getUser()