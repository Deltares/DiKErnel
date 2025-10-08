namespace DiKErnel.Core
{
    /// <summary>
    /// Interface for handling log messages.
    /// </summary>
    public interface ILogHandler
    {
        /// <summary>
        /// Logs an info message.
        /// </summary>
        /// <param name="message">The message to log.</param>
        void Info(string message);

        /// <summary>
        /// Logs a warning message.
        /// </summary>
        /// <param name="message">The message to log.</param>
        void Warning(string message);

        /// <summary>
        /// Logs an error message.
        /// </summary>
        /// <param name="message">The message to log.</param>
        void Error(string message);
    }
}