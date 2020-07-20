
#include"Core.h"
namespace gameEngine {
	class FUN_API Application {
	public:
		Application() {

		}
		virtual ~Application(){}
		void run() {
			while (true);
		}
	};
	Application* createApplication();
}
