#ifndef CENTRAL_ENGINE_H
#define CENTRAL_ENGINE_H

/**
 * @file central_engine.h
 * @brief declaration of class 
 *              central_engine
 * @author Hayk Khachatryan
 */

/**
 * @class central_engine
 * @brief Central engine to
 *        handle program initialization,
 *        uninitialization, command-line, e.t.c.
 */
class central_engine
{
    /// @name Program handling management
    /// @{
public:
    /**
     * @brief Runs...
     */
    void run();

private:
    /**
     * @brief Makes initialization
     */
    void init();

private:
    /**
     * @brief Makes initialization of
     *        command processor.
     */
    void init_cmd_processor();

private:
    /**
     * @brief Makes uninitialization
     */
    void uninit();

private:
    /**
     * @brief Makes uninitialization of
     *        command processor.
     */
    void uninit_cmd_processor();
    /// @}

    /// @name singleton management
    /// @{
public:
    /**
     * @brief Gets singletone object.
     */
    static central_engine& get_instance();

public:
    /**
     * @brief Intstantiates singletone object.
     */
    static void instantiate();

public:
    /**
     * @brief Destroys singletone object.
     */
    static void destroy();

private:
    static central_engine* s_instance;
    /// @}

    /// @name Special member functions.
    /// @{
public:
    /**
     * @brief Constructor
     */
    central_engine();

public:
    /**
     * @brief Destructor.
     */
    ~central_engine();
private:
    central_engine(const central_engine&) = delete;
    central_engine& operator=(const central_engine&) = delete;
    /// @}

}; // end of class central_engine

#endif //CENTRAL_ENGINE_H
