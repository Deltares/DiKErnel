namespace DiKErnel.Core
{
    /// <summary>
    /// Interface for handling log messages.
    /// </summary>
    public interface ILogHandler
    {
        /// <summary>
        /// Logs a warning message.
        /// </summary>
        /// <param name="message">The message to log.</param>
        void LogWarning(string message);

        /// <summary>
        /// Logs an error message.
        /// </summary>
        /// <param name="message">The message to log.</param>
        void LogError(string message);
    }
}