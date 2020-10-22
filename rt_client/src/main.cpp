#include "GUI.hpp"
#include <iostream>
#include <mutex>
#include <list>
#include <thread>
#include <atomic>
void     run_client(const char *ipAddress, 
                    std::mutex &recv_mutex,
                    std::list<t_raytrace_data> &updates,
                    std::atomic<bool> &isRunning,
                    std::atomic<bool> &pixelsLoaded,
                    uint32_t *pixels);

// 

int		main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "Specify ip! i.e. 127.0.0.1\n";
		return 0;
	}
	std::mutex l_mutex;
	std::list<t_raytrace_data> updates;
	std::atomic<bool> isRunning;
	std::atomic<bool> imageLoaded;
	uint32_t			shared_pixels[500*500];
	GUI gui;
	
	if (gui.InitGraphics() == false)
		return 1;
	isRunning = true;
	imageLoaded = false;
	gui.setPixels(shared_pixels);
	std::thread clientThread
	( &run_client
		, argv[1]
		, std::ref(l_mutex)
		, std::ref(updates)
		, std::ref(isRunning)
		, std::ref(imageLoaded)
		, std::ref(shared_pixels)
	);

	while (isRunning)
	{
		gui.events(isRunning, imageLoaded);
		gui.update(l_mutex);
		gui.render();
		if (gui.stateChanged())
			updates.push_back(gui.getFlags());
	}
	clientThread.join();
	// client();
    return 0;
}


// void	ft_mainloop()
// {
// 	GUI gui;
	
//     while (running)
//     {
//         events();
//         update();
// 		render();
//     }

// }

// int		main(int argc, char **argv)
// {
// 	std::cout << "Hello World!" << std::endl;
// 	std::cout << argv[argc - 1] << std::endl;
// 	return (0);
// }